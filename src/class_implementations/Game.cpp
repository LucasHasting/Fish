#include <SFML/Graphics.hpp>
#include <unistd.h>

#include "../class_headers/Stage.h"
#include "../class_headers/Game.h"
#include "../class_headers/GameConstants.h"
#include "../class_headers/GameStates.h"
#include <iostream>
#include <SFML/Audio/Music.hpp>

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


void Game::playFile(std::string songFile, int musicIndex){
    if(!musicPlaying[musicIndex]){
          if(currentMusic != nullptr){
              currentMusic->stop();
          }
          currentMusic = std::make_shared<Music>();
          currentMusic->openFromFile(songFile);
          currentMusic->play();
          currentMusic->setLoop(true);
          musicPlaying[musicIndex] = true;
     }
}

void Game::playMusic(){
    switch(gameState){
        case MAIN_MENU:
        case STAGE_MENU:
            musicPlaying[1] = false;
            musicPlaying[2] = false;
            playFile("music/menuMusic.wav", 0);
            break;
        case STAGE_1:
            musicPlaying[0] = false;
            playFile("music/Stage1.wav", 1);
            break;    
        case STAGE_2:
            musicPlaying[0] = false;
            playFile("music/Stage2.wav", 2);
            break;
    }
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
    playMusic();
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
        case STAGE_2:
            stages[1]->driver(window);
            break;
    }
}

void Game::constructStages(){
    //Stage 1 - example descriptions for future stages
    stages.push_back(std::make_shared<Stage>(
        "Stage1",     //the name of the stage (folder used for rounds)
        2,            //max rounds for the stage
        "newBackground.png"
    ));

    stages.push_back(std::make_shared<Stage>(
        "Stage2",
        2,
        "lavaBackgroundNew.png"
    ));
    
    for(unsigned long int i = 0; i < stages.size(); ++i){
        stages[i]->setGameState(&gameState);
    }
}
