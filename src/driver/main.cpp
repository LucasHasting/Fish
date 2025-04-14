#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <unistd.h>
#include "../class_headers/Stage.h"
#include "../class_headers/Game.h"
#include "../class_headers/GameConstants.h"

using namespace sf;

int main(int argc, char const *argv[])
{
    //create the game
    std::shared_ptr<Game> game = std::make_shared<Game>();
    
    //play the game
    game->driverShell();

    //program finished :)
    return 0;
}
