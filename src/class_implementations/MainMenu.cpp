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
 
MainMenu::MainMenu(){
    //create the buttons
    stageButton = std::make_shared<NewSprite>(spriteLocation + "button.png");
    quitButton = std::make_shared<NewSprite>(spriteLocation + "button.png");

    //place the buttons
    stageButton->sprite->setPosition(CENTER_X-(TILE_SIZE/2), CENTER_Y-(TILE_SIZE/2));
    quitButton->sprite->setPosition(CENTER_X-(TILE_SIZE/2), CENTER_Y-(TILE_SIZE/2) + TILE_SIZE*2);
}

void MainMenu::driver(std::shared_ptr<sf::RenderWindow> window){
    this->window = window;

    //draw and buttons
    window->draw(*(stageButton->sprite));
    window->draw(*(quitButton->sprite));

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
