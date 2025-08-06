#pragma once

#include "Shader.h"

class Cuboid {
public:
    Cuboid(float width, float height, float depth);
    void Draw(Shader& shader);

private:
    unsigned int VAO, VBO;
};
