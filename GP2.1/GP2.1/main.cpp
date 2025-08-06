#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Game.h"

int main() {
    Game game(800, 600);
    game.Run();
    return 0;
}
