#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>

Model::Model(Drawable* mesh)
    : mesh(mesh), position(0.0f), rotation(0.0f), scale(1.0f) {}

void Model::Draw(Shader& shader) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    model = glm::scale(model, scale);
    shader.setMat4("model", model);

    mesh->Draw(shader);
}

