#include <SFML/Graphics.hpp>
#include <unistd.h>

#include "../class_headers/Stage.h"
#include "../class_headers/Game.h"
#include "../class_headers/GameConstants.h"
#include "../class_headers/States.h"

using namespace sf;

Game::Game(){
    //set the first game state
    gameState = STAGE_1;

    currentStage = std::make_shared<Stage>("square.png", "Stage1.txt");

    //allocate necessary variables
    window = std::make_shared<RenderWindow>(sf::VideoMode(WIDTH,HEIGHT), TITLE);
    camera = std::make_shared<View>(FloatRect(WIDTH, WIDTH, HEIGHT, HEIGHT));

    //set camera center to (0, 0)
    camera->setCenter(0.f, 0.f);
    
    //set the camera to the window
    window->setView(*camera);
}

void Game::driverShell(){
    while (window->isOpen())
    {
        //check to close the game
        sf::Event event;
        while (window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                window->close();
            }
        }

        //clear the screen
        window->clear();

        //use the current state's driver function
        gameDriver();

        //set the FPS
        usleep(FPS);
    }
}

void Game::gameDriver(){
    //use the current state's driver function
    switch(gameState){
        case MAIN_MENU:
            break;
        case STAGE_1:
            currentStage->driver(window);
            break;
    }
}

