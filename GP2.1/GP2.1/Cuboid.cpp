#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Cuboid.h"


Cuboid::Cuboid(float width, float height, float depth) {
    float w = width / 2.0f;
    float h = height / 2.0f;
    float d = depth / 2.0f;

    float vertices[] = {
        // positions           // normals           // texcoords
        // Back face
        -w, -h, -d,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         w, -h, -d,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         w,  h, -d,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         w,  h, -d,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -w,  h, -d,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -w, -h, -d,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        // Front face
        -w, -h,  d,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
         w, -h,  d,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
         w,  h,  d,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
         w,  h,  d,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
        -w,  h,  d,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
        -w, -h,  d,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

        // Left face
        -w,  h,  d, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -w,  h, -d, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -w, -h, -d, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -w, -h, -d, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -w, -h,  d, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -w,  h,  d, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        // Right face
         w,  h,  d,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         w, -h, -d,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         w,  h, -d,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         w, -h, -d,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         w,  h,  d,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         w, -h,  d,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,

         // Bottom face
         -w, -h, -d,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
          w, -h, -d,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
          w, -h,  d,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
          w, -h,  d,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         -w, -h,  d,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
         -w, -h, -d,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

         // Top face
         -w,  h, -d,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
          w,  h, -d,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
          w,  h,  d,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
          w,  h,  d,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         -w,  h,  d,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
         -w,  h, -d,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // TexCoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Cuboid::Draw(Shader& shader) {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
