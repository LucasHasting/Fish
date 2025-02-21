#ifndef STAGE_H
#define STAGE_H

#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <string>
#include "NewSprite.h"

using namespace sf;

class Stage{
    private:
        std::string spriteLocation = "sprites/";
        std::string exampleSpriteName = spriteLocation + "square.png";
        std::shared_ptr<NewSprite> exampleSprite = nullptr;
    public:
        Stage();
        void driver(std::shared_ptr<sf::RenderWindow>);
};

#endif
