#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <string>
#include "NewSprite.h"
#include "Screen.h"
#include "GameConstants.h"

using namespace sf;

class MainMenu : public Screen{
    private:
        std::shared_ptr<NewSprite> stageButton = nullptr;
        std::shared_ptr<NewSprite> quitButton = nullptr;
        std::shared_ptr<NewSprite> background = nullptr;
    public:
        MainMenu();
        void driver(std::shared_ptr<RenderWindow>) override;
};

#endif
