#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <unistd.h>

#include "../class_headers/Screen.h"
#include "../class_headers/Stage.h"
#include "../class_headers/NewSprite.h"
#include "../class_headers/GameConstants.h"

using namespace sf;

Stage::Stage(std::string pathSpriteLocation, std::string pathFileLocation){
    //set the files for the stage
    this->pathSpriteLocation += pathSpriteLocation;
    this->pathFileLocation += pathFileLocation;

    //set the path sprite
    pathSprite = std::make_unique<NewSprite>(this->pathSpriteLocation);
    pathSprite->sprite->setPosition(0.f, 0.f);
}

void Stage::driver(std::shared_ptr<sf::RenderWindow> window) {
    //draw to the screen
    window->draw(*(pathSprite->sprite));

    //display the screen
    window->display();
}

void Stage::constructPath() {}
