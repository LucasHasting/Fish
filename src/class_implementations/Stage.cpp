#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <iostream>

#include "../class_headers/Screen.h"
#include "../class_headers/Stage.h"
#include "../class_headers/NewSprite.h"
#include "../class_headers/GameConstants.h"

using namespace sf;

Stage::Stage(std::string pathSpriteLocation, std::string pathFileLocation){
    //set the files for the stage
    this->pathSpriteLocation += pathSpriteLocation;
    this->pathFileLocation += pathFileLocation;
    
    //construct the path
    constructPath();
}

void Stage::driver(std::shared_ptr<sf::RenderWindow> window) {
    //draw to the screen
    drawPath(window);

    //display the screen
    window->display();
}

void Stage::constructPath() {
    //create input file stream
    std::ifstream pathFile(pathFileLocation);
    
    //stop the program if it could not open the file
    if(!pathFile.is_open()){
        exit(1);
    }

    //store the path into a variable
    std::string path_string;
    std::getline(pathFile, path_string);

    //close the path file
    pathFile.close();

    //declare vector for amount of sprite
    std::vector<int> sprite_count;

    //declare vector for direction
    std::vector<char> direction;

    //loop through the path string and add contents to corresponding vectors
    for(int i = 0; path_string[i] != '0'; i += 2){
        sprite_count.push_back(path_string[i] + ASCII_SHIFT);
        direction.push_back(path_string[i+1]);
    }
    
    //set initial position
    Vector2f initial_position = {FIRST_TILE_CENTER_X, FIRST_TILE_CENTER_Y};
    initial_position = calculate_position(initial_position, direction[0], sprite_count[0]);
    
    //set all sprites in the path
    for(long unsigned int i = 1; i < sprite_count.size(); ++i){
        for(int j = 0; j < sprite_count[i]; ++j){
            //set position of sprite
            path.push_back(std::make_shared<NewSprite>(pathSpriteLocation));
            path[path.size()-1]->sprite->setPosition(initial_position);

            //update position
            initial_position = calculate_position(initial_position, direction[i], 1);
        }
    }
}

Vector2f Stage::calculate_position(Vector2f initial_pos, char direction, int count){
    switch(direction){
        case 'u':
            initial_pos.y -= TILE_SIZE * count;
            break;
        case 'd':
            initial_pos.y += TILE_SIZE * count;
            break;
        case 'l':
            initial_pos.x -= TILE_SIZE * count;
            break;
        case 'r':
            initial_pos.x += TILE_SIZE * count;
            break;
    }
    return initial_pos;
}

void Stage::drawPath(std::shared_ptr<sf::RenderWindow> window) {
    for(long unsigned int i = 0; i < path.size(); ++i){
        window->draw(*(path[i]->sprite));
    }
}
