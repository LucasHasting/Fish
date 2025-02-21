#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <unistd.h>

#include "../class_headers/Stage.h"
#include "../class_headers/NewSprite.h"
#include "../class_headers/GameConstants.h"

using namespace sf;

//may need to be overidden per stage we have, the basic layout of the stage
Stage::Stage(){ 
    //set the sprite
    exampleSprite = std::make_unique<NewSprite>(exampleSpriteName);

    //set the sprite's position
    exampleSprite->sprite->setPosition(0.f, 0.f);
}

void Stage::driver(std::shared_ptr<sf::RenderWindow> window){
    //draw to the screen
    window->draw(*(exampleSprite->sprite));

    //display the screen
    window->display();
}