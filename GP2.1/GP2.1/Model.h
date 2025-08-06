// Model.h
#pragma once
#include <glm/glm.hpp>
#include "Shader.h"

class Drawable {
public:
    virtual void Draw(Shader& shader) = 0;
    virtual ~Drawable() {}
};

class Model {
public:
    Model(Drawable* mesh);  // <-- this line must exist

    void Draw(Shader& shader);

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

private:
    Drawable* mesh;
};
