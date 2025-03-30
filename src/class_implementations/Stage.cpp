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
#include "../class_headers/Enemy.h"
#include "../class_headers/GameConstants.h"
#include "../class_headers/GameStates.h"

using namespace sf;

Stage::Stage(std::string pathSpriteLocation, std::string pathFileLocation, std::string stageName, int maxRounds){
    //default to tower menu
    stageState = TOWER;
    
    //set the files for the stage
    this->pathSpriteLocation += pathSpriteLocation;
    this->pathFileLocation += pathFileLocation;
    this->enemyFileLocation += stageName + "/round#.txt";
    this->maxRounds = maxRounds;
    this->currentRound = 1; //start at the first round

    //create the button for the rounds
    button = std::make_shared<NewSprite>(spriteLocation + "button.png");

    //place button in bottom corner
    button->sprite->setPosition(WIDTH/4,(HEIGHT/3)+TILE_SIZE);
    
    //construct the path
    constructPath();
}

void Stage::driver(std::shared_ptr<sf::RenderWindow> window) {
    Vector2i mpos = Mouse::getPosition(*window); 
    std::cout << mpos.x << "\t" << mpos.y << std::endl;

    switch(stageState){
        case ROUND:
            //draw the path to the screen
            drawPath(window);
            
            //draw enemies to the screen
            drawEnemies(window);

            //display the screen
            window->display();

            //update enemy location
            moveEnemies();

            //decrement frame count (mod 32)
            frame_count--;
            break;
        case TOWER:
            if(currentRound > maxRounds){
                stageState = FINISHED;
                break;
            }

            //change frame count for later - low cost overall, will stay
            frame_count = TILE_SIZE;

            //draw the path to the screen
            drawPath(window);

            //draw the button for the next round
            window->draw(*(button->sprite));

            //display the screen
            window->display();

            //check if the button has been clicked
            if(isButtonClicked(window)){
                //reset enemy round vectors
                roundEnemies.clear();
                correspondingTile.clear();

                //construct the round and start the round
                constructRound(currentRound);
                currentRound++;
                stageState = ROUND;
            }
        case FINISHED:
            
            //display the window
            window->display();
            break;
    }
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
        
    std::vector<char> direction;
    std::vector<int> sprite_count;

    //loop through the path string and add contents to corresponding vectors
    for(int i = 0; path_string[i] != '0'; i += 2){
        sprite_count.push_back(path_string[i] + ASCII_SHIFT);
        direction.push_back(path_string[i+1]);
    }
    
    //set initial position
    Vector2f initial_position = {FIRST_TILE_CENTER_X, FIRST_TILE_CENTER_Y};
    initial_position = calculate_position(initial_position, direction[0], sprite_count[0], TILE_SIZE);
    
    //set all sprites in the path
    for(long unsigned int i = 1; i < sprite_count.size(); ++i){
        for(int j = 0; j < sprite_count[i]; ++j){
            //set position of sprite
            path.push_back(std::make_shared<NewSprite>(pathSpriteLocation));
            path[path.size()-1]->sprite->setPosition(initial_position);

            //update position
            initial_position = calculate_position(initial_position, direction[i], 1, TILE_SIZE);

            //save the direction of the sprite into a vector
            directions.push_back(direction[i]);
        }
    }
}

void Stage::constructRound(int round){
    //convert round to char
    char roundChar = round - ASCII_SHIFT;

    //change round file
    enemyFileLocation[enemyFileLocation.size()-5] = roundChar;

    //create input file stream
    std::ifstream enemyFile(enemyFileLocation);
    
    //stop the program if it could not open the file
    if(!enemyFile.is_open()){
        exit(1);
    }

    //store the enemies into a variable
    std::string enemy_string;
    std::getline(enemyFile, enemy_string);

    //close the path file
    enemyFile.close();

    //declare vector for amount of enemies
    std::vector<int> enemy_count;

    //declare vector for enemy type
    std::vector<char> enemy_type;
    
    //loop through the path string and add contents to corresponding vectors
    for(int i = 0; enemy_string[i] != '0'; i += 2){
        enemy_count.push_back(enemy_string[i] + ASCII_SHIFT);
        enemy_type.push_back(enemy_string[i+1]);
    }
    
    //get initial pos for the enemies
    Vector2f currentEnemyPos = path[0]->sprite->getPosition();
    int initial = 0;

    //set all sprites in the path
    for(long unsigned int i = 0; i < enemy_count.size(); ++i){
        for(int j = 0; j < enemy_count[i]; ++j){
            //get enemy type
            std::string location_of_enemy = getEnemyType(enemy_type[i]);

            //set position of enemy
            roundEnemies.push_back(std::make_shared<Enemy>(spriteLocation + location_of_enemy, 1, 1));
            roundEnemies[roundEnemies.size()-1]->sprite->setPosition(currentEnemyPos);
            correspondingTile.push_back(initial);
            initial--;

            //update position
            currentEnemyPos.x -= TILE_SIZE;
        }
    }
}

std::string Stage::getEnemyType(char type){
    switch(type){
        case 'r':
            return "red_square.png";
        case 'b':
            return "blue_square.png";
        default:
            return "none";
    }
}

Vector2f Stage::calculate_position(Vector2f initial_pos, char direction, int count, int size){
    switch(direction){
        case 'u':
            initial_pos.y -= size * count;
            break;
        case 'd':
            initial_pos.y += size * count;
            break;
        case 'l':
            initial_pos.x -= size * count;
            break;
        case 'r':
            initial_pos.x += size * count;
            break;
    }
    return initial_pos;
}

void Stage::drawPath(std::shared_ptr<sf::RenderWindow> window) {
    for(long unsigned int i = 0; i < path.size(); ++i){
        window->draw(*(path[i]->sprite));
    }
}

void Stage::drawEnemies(std::shared_ptr<sf::RenderWindow> window) {
    for(long unsigned int i = 0; i < roundEnemies.size(); ++i){
        window->draw(*(roundEnemies[i]->sprite));
    }
}

void Stage::moveEnemies(){
    //std::cout << correspondingTile[(int) correspondingTile.size() - 1] << "\t" << directions.size() << std::endl;
    
    if(correspondingTile[(int) correspondingTile.size() - 1] >= (int) directions.size() - 1){
        stageState = TOWER;
        return;
    }

    if(frame_count == 0){
        for(long unsigned int i = 0; i < roundEnemies.size(); ++i){
            correspondingTile[i] += 1;
        }
        frame_count = TILE_SIZE;
    }

    for(long unsigned int i = 0; i < roundEnemies.size(); ++i){
        //sprite has reached the end
        if((long unsigned int)correspondingTile[i] == directions.size() - 1){
            roundEnemies[i]->sprite->setColor(Color::Transparent); 
            continue;
        }

        //get the enemy location
        Vector2f currentEnemyPos = roundEnemies[i]->sprite->getPosition();
        
        //update position
        if(correspondingTile[i] < 0){
            currentEnemyPos.x += 1;
        } else {
            currentEnemyPos = calculate_position(currentEnemyPos, directions[correspondingTile[i]], 1, 1);
        }

        //set the position
        roundEnemies[i]->sprite->setPosition(currentEnemyPos);
    }
}

bool Stage::isButtonClicked(std::shared_ptr<sf::RenderWindow> window){
    if(Mouse::isButtonPressed(Mouse::Left)){
        Vector2f mouse = window->mapPixelToCoords(Mouse::getPosition(*window));

        FloatRect bounds = button->sprite->getGlobalBounds();

        return (bounds.contains(mouse));
    }
    return false;
}
