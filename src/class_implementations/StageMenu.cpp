#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <string>
#include <iostream>
#include "../class_headers/Screen.h"
#include "../class_headers/GameConstants.h"
#include "../class_headers/NewSprite.h"
#include "../class_headers/MainMenu.h"
#include "../class_headers/StageMenu.h"
#include "../class_headers/GameStates.h"
 
StageMenu::StageMenu(){
    //create the buttons
    stageOneButton = std::make_shared<NewSprite>(spriteLocation + "oneButton.png");
    stageTwoButton = std::make_shared<NewSprite>(spriteLocation + "twoButton.png");

    //place the buttons
    stageOneButton->sprite->setPosition(CENTER_X-(TILE_SIZE/2), CENTER_Y-(TILE_SIZE/2) - TILE_SIZE*4);
    stageTwoButton->sprite->setPosition(CENTER_X-(TILE_SIZE/2), CENTER_Y-(TILE_SIZE/2) - TILE_SIZE*2);
}

void StageMenu::driver(std::shared_ptr<sf::RenderWindow> window){
    this->window = window;

    //draw and buttons
    window->draw(*(stageOneButton->sprite));
    window->draw(*(stageTwoButton->sprite));

    window->display();

    //if the stage button has been clicked, go to stage menu
    if(isClicked(stageOneButton)){
        *gs = STAGE_1;        
    }
    
    if(isClicked(stageTwoButton)){
        *gs = STAGE_2;        
    }
}
