#include "Model.h"

class Sphere : public Drawable {
public:
    Sphere(unsigned int segments = 32, unsigned int rings = 32);
    void Draw(Shader& shader) override;

private:
    unsigned int VAO, VBO, indexCount;
};

