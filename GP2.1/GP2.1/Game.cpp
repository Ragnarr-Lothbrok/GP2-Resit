#include "Game.h"
#include "Texture.h"
#include "PathConfig.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <iostream>

Game::Game(unsigned int width, unsigned int height)
    : SCR_WIDTH(width), SCR_HEIGHT(height), window(nullptr),
    shader(nullptr), cube(nullptr), cuboid(nullptr), sphere(nullptr),
    cubeTex(0), cuboidTex(0), sphereTex(0) {}

Game::~Game() {
    delete shader;
    delete cube;
    delete cuboid;
    delete sphere;
    glfwTerminate();
}

bool Game::Init() {
    if (!glfwInit()) return false;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "3D Game", NULL, NULL);
    if (!window) return false;

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int w, int h) {
        glViewport(0, 0, w, h);
        });

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return false;

    glEnable(GL_DEPTH_TEST);
    return true;
}

void Game::LoadAssets() {
    shader = new Shader(
        GetShaderPath("shader.vert").c_str(),
        GetShaderPath("shader.frag").c_str()
    );

    cube = new Cube();
    cuboid = new Cuboid(2.0f, 1.0f, 1.0f);
    sphere = new Sphere();

    cubeTex = LoadTexture(GetTexturePath("cube_texture.jpg").c_str());
    cuboidTex = LoadTexture(GetTexturePath("cuboid_texture.jpg").c_str());
    sphereTex = LoadTexture(GetTexturePath("sphere_texture.jpg").c_str());
}

void Game::ProcessInput(float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Toggle freeze camera
    static bool spaceLast = false;
    bool spaceNow = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
    if (spaceNow && !spaceLast) freezeCamera = !freezeCamera;
    spaceLast = spaceNow;

    // Toggle camera mode
    static bool cLast = false;
    bool cNow = glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS;
    if (cNow && !cLast) cameraMode = (cameraMode == CameraMode::ORBIT) ? CameraMode::FIXED : CameraMode::ORBIT;
    cLast = cNow;

    // Toggle sphere bounce
    static bool bLast = false;
    bool bNow = glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS;
    if (bNow && !bLast) sphereBounce = !sphereBounce;
    bLast = bNow;

    float moveSpeed = 2.0f;
    float rotSpeed = 90.0f;

    // --- Cube movement ---
    glm::vec3 cubeNext = cubePos;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        cubeNext.x -= moveSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        cubeNext.x += moveSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        cubeNext.y += moveSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        cubeNext.y -= moveSpeed * deltaTime;

    AABB cubeBox = { cubeNext, glm::vec3(0.5f) };
    AABB cuboidBox = { cuboidPos, glm::vec3(1.0f, 0.5f, 0.5f) };
    AABB sphereBox = { spherePos, glm::vec3(0.5f) };

    if (!CheckCollision(cubeBox, cuboidBox) && !CheckCollision(cubeBox, sphereBox))
        cubePos = cubeNext;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cubeRotationY -= rotSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cubeRotationY += rotSpeed * deltaTime;

    // --- Cuboid movement ---
    glm::vec3 cuboidNext = cuboidPos;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        cuboidNext.x -= moveSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        cuboidNext.x += moveSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        cuboidNext.y += moveSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        cuboidNext.y -= moveSpeed * deltaTime;

    cubeBox = { cubePos, glm::vec3(0.5f) };
    sphereBox = { spherePos, glm::vec3(0.5f) };
    AABB nextCuboidBox = { cuboidNext, glm::vec3(1.0f, 0.5f, 0.5f) };

    if (!CheckCollision(nextCuboidBox, cubeBox) && !CheckCollision(nextCuboidBox, sphereBox))
        cuboidPos = cuboidNext;

    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        cuboidRotationY -= rotSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        cuboidRotationY += rotSpeed * deltaTime;

    // --- Sphere movement ---
    glm::vec3 sphereNext = spherePos;

    // X-axis movement
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        sphereNext.x -= moveSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        sphereNext.x += moveSpeed * deltaTime;

    // Y-axis movement
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        sphereNext.y += moveSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        sphereNext.y -= moveSpeed * deltaTime;

    cubeBox = { cubePos, glm::vec3(0.5f) };
    cuboidBox = { cuboidPos, glm::vec3(1.0f, 0.5f, 0.5f) };
    AABB nextSphereBox = { sphereNext, glm::vec3(0.5f) };

    //Save original Y before applying movement
    float originalY = spherePos.y;

    if (!CheckCollision(nextSphereBox, cubeBox) && !CheckCollision(nextSphereBox, cuboidBox)) {
        spherePos = sphereNext;

        //Only update baseY if Y has changed (to preserve bounce origin)
        if (sphereNext.y != originalY)
            sphereBaseY = spherePos.y;

        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            sphereRotationY -= rotSpeed * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            sphereRotationY += rotSpeed * deltaTime;
    }
}

void Game::Update() {
    float bounceSpeed = 2.0f;
    float bounceAmp = 1.0f;

    if (sphereBounce) {
        sphereBounceT = glfwGetTime();
        spherePos.y = sphereBaseY + bounceAmp * std::abs(std::sin(sphereBounceT * bounceSpeed));
    }

    // Collision logs
    AABB cubeBox = { cubePos, glm::vec3(0.5f) };
    AABB cuboidBox = { cuboidPos, glm::vec3(1.0f, 0.5f, 0.5f) };
    AABB sphereBox = { spherePos, glm::vec3(0.5f) };

    if (CheckCollision(cubeBox, cuboidBox))
        std::cout << "Cube <-> Cuboid COLLISION!\n";
    if (CheckCollision(cubeBox, sphereBox))
        std::cout << "Cube <-> Sphere COLLISION!\n";
    if (CheckCollision(cuboidBox, sphereBox))
        std::cout << "Cuboid <-> Sphere COLLISION!\n";
}

void Game::Render() {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->use();

    static float lastAngle = 0.0f;
    float angle = freezeCamera ? lastAngle : glfwGetTime();
    if (!freezeCamera) lastAngle = angle;

    float radius = 15.0f;
    glm::vec3 camPos = (cameraMode == CameraMode::ORBIT)
        ? glm::vec3(sin(angle) * radius, 0.0f, cos(angle) * radius)
        : glm::vec3(0.0f, 10.0f, 20.0f);

    glm::mat4 view = glm::lookAt(camPos, glm::vec3(0.0f), glm::vec3(0, 1, 0));
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);

    shader->setMat4("view", view);
    shader->setMat4("projection", proj);
    shader->setVec3("viewPos", camPos);
    shader->setVec3("lightPos", glm::vec3(5.0f, 5.0f, 5.0f));
    shader->setVec3("lightColor", glm::vec3(1.0f));
    shader->setVec3("objectColor", glm::vec3(1.0f));

    glm::mat4 model;

    // Cube
    glBindTexture(GL_TEXTURE_2D, cubeTex);
    model = glm::translate(glm::mat4(1.0f), cubePos);
    model = glm::rotate(model, glm::radians(cubeRotationY), glm::vec3(0, 1, 0));
    shader->setMat4("model", model);
    cube->Draw(*shader);

    // Cuboid
    glBindTexture(GL_TEXTURE_2D, cuboidTex);
    model = glm::translate(glm::mat4(1.0f), cuboidPos);
    model = glm::rotate(model, glm::radians(cuboidRotationY), glm::vec3(0, 1, 0));
    shader->setMat4("model", model);
    cuboid->Draw(*shader);

    // Sphere
    glBindTexture(GL_TEXTURE_2D, sphereTex);
    model = glm::translate(glm::mat4(1.0f), spherePos);
    model = glm::rotate(model, glm::radians(sphereRotationY), glm::vec3(0, 1, 0));
    shader->setMat4("model", model);
    sphere->Draw(*shader);
}

void Game::Run() {
    if (!Init()) return;
    LoadAssets();

    float last = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        float now = glfwGetTime();
        float dt = now - last;
        last = now;

        ProcessInput(dt);
        Update();
        Render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

bool Game::CheckCollision(const AABB& a, const AABB& b) {
    return (std::abs(a.center.x - b.center.x) <= (a.halfSize.x + b.halfSize.x)) &&
        (std::abs(a.center.y - b.center.y) <= (a.halfSize.y + b.halfSize.y)) &&
        (std::abs(a.center.z - b.center.z) <= (a.halfSize.z + b.halfSize.z));
}
