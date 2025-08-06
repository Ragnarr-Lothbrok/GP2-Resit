#include "Model.h"

class Cube : public Drawable {
public:
    Cube();
    void Draw(Shader& shader) override;

private:
    unsigned int VAO, VBO;
};
