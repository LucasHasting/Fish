#include <SFML/Graphics.hpp>
#include <unistd.h>

#include "../class_headers/Stage.h"
#include "../class_headers/Game.h"
#include "../class_headers/GameConstants.h"
#include "../class_headers/GameStates.h"
#include <iostream>
#include <SFML/Audio/Music.hpp>

using namespace sf;

//Construct the game
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

    //allocate the window and set the camera's position
    window = std::make_shared<RenderWindow>(VideoMode(WIDTH,HEIGHT), TITLE);
    camera = std::make_shared<View>(FloatRect(WIDTH, WIDTH, HEIGHT, HEIGHT));

    //set the camera to the center 
    camera->setCenter(CENTER_X, CENTER_Y);
    
    //set the camera to the window
    window->setView(*camera);
}


//method used to set the current song and play it
void Game::playFile(std::string songFile, int musicIndex){
    //if the current song is not playing
    if(!musicPlaying[musicIndex]){
        //if a song has been set, stop it  
        if(currentMusic != nullptr){
              currentMusic->stop();
        }

        //set the current song from a file
        currentMusic = std::make_shared<Music>();
        currentMusic->openFromFile(songFile);

        //play the song and set it to loop
        currentMusic->play();
        currentMusic->setLoop(true);

        //set the current song to playing
        musicPlaying[musicIndex] = true;
     }
}

//method used to play the current state's music
void Game::playMusic(){
    //select the current state's music and set all other tracks to false
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

//method works as the shell for the driver
void Game::driverShell(){
    while (window->isOpen())
    {
        //check to close the game
        Event event;
        while (window->pollEvent(event))
        {
            if(event.type == Event::Closed){
                window->close();
            }
        }

        //clear the screen
        window->clear();

        //use the current state's driver method
        gameDriver();

        //set the FPS
        usleep(FPS);
    }
}

//method selects the current state's driver
void Game::gameDriver(){
    //play the current state's song
    playMusic();

    //use the current state's driver method
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

//method used to construct the stage
void Game::constructStages(){
    //Stage 1 - example descriptions for future stages
    stages.push_back(std::make_shared<Stage>(
        "Stage1",           //the name of the stage (folder used for rounds and the path file)
        2,                  //max rounds for the stage
        "newBackground.png" //name of the background image
    ));

    //Create stage 2
    stages.push_back(std::make_shared<Stage>(
        "Stage2",
        2,
        "lavaBackgroundNew.png"
    ));
    
    //Loop through the stages and set the address of the game state so the stage
    //can change the game's state
    for(unsigned long int i = 0; i < stages.size(); ++i){
        stages[i]->setGameState(&gameState);
    }
}
