#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "Stage.h"
#include "States.h"

using namespace sf;

class Game {
    private:
        enum States gameState;
        std::shared_ptr<Stage> currentStage = nullptr;
        std::shared_ptr<View> camera = nullptr;
        std::shared_ptr<RenderWindow> window = nullptr;
        void gameDriver();
    public:
        Game();
        void driverShell();
};

#endif
