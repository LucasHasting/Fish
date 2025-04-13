#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "Stage.h"
#include "MainMenu.h"
#include "StageMenu.h"
#include "GameStates.h"
#include <vector>

using namespace sf;

class Game {
    private:
        enum GameStates gameState;
        std::vector<std::shared_ptr<Stage>> stages;
        std::shared_ptr<MainMenu> main;
        std::shared_ptr<StageMenu> sm;
        std::shared_ptr<View> camera = nullptr;
        std::shared_ptr<RenderWindow> window = nullptr;
        void gameDriver();
        void constructStages();
    public:
        Game();
        void driverShell();
};

#endif
