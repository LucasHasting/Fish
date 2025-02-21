#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "Stage.h"

using namespace sf;

class Game {
    private:
        int gameState = 1;
        std::shared_ptr<Stage> currentStage = nullptr;
        std::shared_ptr<View> camera = nullptr;
        std::shared_ptr<RenderWindow> window = nullptr;
    public:
        Game();
        void gameDriver();
        void driverShell();
};

#endif