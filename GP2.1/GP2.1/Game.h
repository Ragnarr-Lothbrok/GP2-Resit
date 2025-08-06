#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Cube.h"
#include "Cuboid.h"
#include "Sphere.h"

enum class CameraMode {
    ORBIT,
    FIXED
};

class Game {
public:
    Game(unsigned int width, unsigned int height);
    ~Game();

    void Run();

private:
    unsigned int SCR_WIDTH;
    unsigned int SCR_HEIGHT;
    GLFWwindow* window;

    Shader* shader;
    Cube* cube;
    Cuboid* cuboid;
    Sphere* sphere;

    unsigned int cubeTex;
    unsigned int cuboidTex;
    unsigned int sphereTex;

    // Updated object positions
    glm::vec3 cubePos = glm::vec3(0.0f, 3.0f, 0.0f);
    glm::vec3 cuboidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 spherePos = glm::vec3(0.0f, -3.0f, 0.0f);

    // Object rotations
    float cubeRotationY = 0.0f;
    float cuboidRotationY = 0.0f;
    float sphereRotationY = 0.0f;

    // Camera
    bool freezeCamera = false;
    CameraMode cameraMode = CameraMode::ORBIT;

    // Sphere bounce
    float sphereBaseY = -3.0f;       //bounce now happens at Y=0
    float sphereBounceT = 0.0f;
    bool  sphereBounce = false;      //initially off

    // Collision box struct
    struct AABB {
        glm::vec3 center;
        glm::vec3 halfSize;
    };

    bool Init();
    void LoadAssets();
    void ProcessInput(float deltaTime);
    void Update();
    void Render();

    // Collision helper
    bool CheckCollision(const AABB& a, const AABB& b);
};
