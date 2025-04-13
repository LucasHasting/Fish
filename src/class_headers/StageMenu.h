#ifndef STAGE_MENU_H
#define STAGE_MENU_H

#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <string>
#include "NewSprite.h"
#include "Screen.h"
#include "GameConstants.h"

using namespace sf;

class StageMenu : public Screen{
    private:
        std::shared_ptr<NewSprite> stageButton = nullptr;
    public:
        StageMenu();
        void driver(std::shared_ptr<sf::RenderWindow>) override;
};

#endif
