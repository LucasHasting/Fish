#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <unistd.h>
#include "class_headers/Stage.h"
#include "class_headers/Game.h"
#include "class_headers/GameConstants.h"

using namespace sf;

int main(int argc, char const *argv[])
{
    std::shared_ptr<Game> game = std::make_shared<Game>();
    game->driverShell();
    return 0;
}
