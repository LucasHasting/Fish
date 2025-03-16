#ifndef STAGE1_H
#define STAGE1_H

#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <vector>
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
        std::vector<std::shared_ptr<NewSprite>> path;
    public:
        Stage(std::string pathSprite, std::string pathFile);
        void driver(std::shared_ptr<sf::RenderWindow>) override;
        void constructPath();
        Vector2f calculate_position(Vector2f, char, int);
        void drawPath(std::shared_ptr<sf::RenderWindow>);
};

#endif
