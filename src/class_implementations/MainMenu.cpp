#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <string>
#include <iostream>
#include "../class_headers/Screen.h"
#include "../class_headers/GameConstants.h"
#include "../class_headers/NewSprite.h"
#include "../class_headers/MainMenu.h"
#include "../class_headers/GameStates.h"
 
//construct the main menu
MainMenu::MainMenu(){
    //create the buttons and the background
    stageButton = std::make_shared<NewSprite>(spriteLocation + "menuButton.png");
    quitButton = std::make_shared<NewSprite>(spriteLocation + "quitButton.png");
    background = std::make_shared<NewSprite>(spriteLocation + "mainMenu.png");

    //place the buttons and the background
    stageButton->sprite->setPosition(CENTER_X-(TILE_SIZE/2), CENTER_Y-(TILE_SIZE/2));
    quitButton->sprite->setPosition(CENTER_X-(TILE_SIZE/2), CENTER_Y-(TILE_SIZE/2) + TILE_SIZE*2);
    background->sprite->setPosition(CENTER_X-(WIDTH/2), CENTER_Y-(HEIGHT/2));
}

//method to display the main menu
void MainMenu::driver(std::shared_ptr<RenderWindow> window){
    this->window = window;

    //draw buttons and background
    window->draw(*(background->sprite));
    window->draw(*(stageButton->sprite));
    window->draw(*(quitButton->sprite));

    //display the screen
    window->display();

    //if the stage button has been clicked, go to stage menu
    if(isClicked(stageButton)){
        *gs = STAGE_MENU;        
    }

    //if the quit button has been clicked, quit the game
    if(isClicked(quitButton)){
        window->close();
    }
}
