#ifndef STAGE1_H
#define STAGE1_H

#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <string>
#include "NewSprite.h"
#include "Screen.h"

using namespace sf;

class Stage : public Screen{
    private:
        std::shared_ptr<NewSprite> pathSprite = nullptr;
        std::string pathLocation = "paths/";
        std::string pathSpriteLocation = spriteLocation; 
        std::string pathFileLocation = pathLocation; 
        std::string path;
    public:
        Stage(std::string pathSprite, std::string pathFile);
        void constructPath();
        void driver(std::shared_ptr<sf::RenderWindow>) override;
};

#endif
