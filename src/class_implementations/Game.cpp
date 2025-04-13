#include <SFML/Graphics.hpp>
#include <unistd.h>

#include "../class_headers/Stage.h"
#include "../class_headers/Game.h"
#include "../class_headers/GameConstants.h"
#include "../class_headers/GameStates.h"
#include <iostream>

using namespace sf;

Game::Game(){
    //set the first game state
    gameState = MAIN_MENU;

    //construct the stages
    constructStages();

    //construct the main menu
    main = std::make_shared<MainMenu>();
    main->setGameState(&gameState);
    
    //construct the stage menu
    sm = std::make_shared<StageMenu>();
    sm->setGameState(&gameState);

    //allocate necessary variables
    window = std::make_shared<RenderWindow>(sf::VideoMode(WIDTH,HEIGHT), TITLE);
    camera = std::make_shared<View>(FloatRect(WIDTH, WIDTH, HEIGHT, HEIGHT));

    //set camera center 
    camera->setCenter(CENTER_X, CENTER_Y);
    
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
            main->driver(window);
            break;
        case STAGE_MENU:
            sm->driver(window);
            break;
        case STAGE_1:
            stages[0]->driver(window);
            break;
    }
}

void Game::constructStages(){
    //Stage 1 - example descriptions for future stages
    stages.push_back(std::make_shared<Stage>(
        "square.png", //path sprite for stage 1
        "Stage1.txt", //the file containing the path itself
        "Stage1",     //the name of the stage (folder used for rounds)
        2             //max rounds for the stage
    ));
    
    stages[0]->setGameState(&gameState);
}
