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

void Stage::reset(){
    health = MAX_HEALTH;
    money = STARTING_AMOUNT;
    
    placedTowers.clear();

    //default to tower menu
    stageState = TOWER;
    
    this->maxRounds = maxRounds;
    this->currentRound = 1; //start at the first round
    
    //place the finished button off screen
    finishedButton->sprite->setPosition(-1000.f, -1000.f);
}

Stage::Stage(std::string stageName, int maxRounds, std::string backgroundSpriteLocation){
    //default to tower menu
    stageState = TOWER;
    
    //set the files for the stage
    this->pathSpriteLocation += "square.png";
    this->pathFileLocation += stageName + ".txt";
    this->enemyFileLocation += stageName + "/round#.txt";
    this->backgroundSpriteLocation += backgroundSpriteLocation;
    this->maxRounds = maxRounds;
    this->currentRound = 1; //start at the first round

    //set fonts
    if(!endFont.loadFromFile("fonts/SuperLobster.ttf")){
        exit(1);
    }
    
    if(!stageFont.loadFromFile("fonts/SpringRainstorm.ttf")){
        exit(1);
    }

    //create the buttons
    button = std::make_shared<NewSprite>(spriteLocation + "button.png");
    finishedButton = std::make_shared<NewSprite>(spriteLocation + "menuButton.png");

    //place the round button in bottom corner
    button->sprite->setPosition(TILE_SIZE, HEIGHT-TILE_SIZE);

    //place the finished button off screen
    finishedButton->sprite->setPosition(-1000.f, -1000.f);
    
    //create the background
    background = std::make_shared<NewSprite>(this->backgroundSpriteLocation);
    background->sprite->setPosition(CENTER_X - (WIDTH/2), CENTER_Y - (HEIGHT/2));

    //construct the path
    constructPath();

    //construct the stage towers
    constructTowers();
}

void Stage::constructTowers(){
    stageTowers.push_back(std::make_shared<Tower>(spriteLocation + "cat1.png", 1, 1));
    stageTowers[stageTowers.size() - 1]->sprite->setPosition(WIDTH-224, 0.0f);
    stageTowers[stageTowers.size() - 1]->sprite->setScale(0.5f, 0.5f);

    stageTowers.push_back(std::make_shared<Tower>(spriteLocation + "cat2.png", 2, 2));
    stageTowers[stageTowers.size() - 1]->sprite->setPosition(WIDTH-224, TILE_SIZE*1.5);
    stageTowers[stageTowers.size() - 1]->sprite->setScale(0.5f, 0.5f);
    
    stageTowers.push_back(std::make_shared<Tower>(spriteLocation + "cat3.png", 3, 3));
    stageTowers[stageTowers.size() - 1]->sprite->setPosition(WIDTH-224, TILE_SIZE * 3);
    stageTowers[stageTowers.size() - 1]->sprite->setScale(0.5f, 0.5f);

    double j = 0;
    for(long unsigned int i = 0; i < stageTowers.size(); ++i, j+=1.5){
        std::string towerCostString = "FP: " + std::to_string(stageTowers[i]->getCost());    
        towerCostText.push_back(std::make_shared<Text>());
        towerCostText[i]->setFont(stageFont);
        towerCostText[i]->setString(towerCostString);
        towerCostText[i]->setCharacterSize(20);
        towerCostText[i]->setFillColor(Color::White);
        towerCostText[i]->setPosition(WIDTH-176, TILE_SIZE * j);
    }
}


void Stage::driver(std::shared_ptr<sf::RenderWindow> window) {
    this->window = window;
    window->draw(*(background->sprite));

    //Vector2i mpos = Mouse::getPosition(*window); 
    //std::cout << mpos.x << "\t" << mpos.y << std::endl;
    
    //prepare round text
    std::string roundString = "Round: " + std::to_string(currentRound - 1) + "/" + std::to_string(maxRounds);

    //prepare stage health text
    std::string healthString = "Health: " + std::to_string(health) + "/" + std::to_string(MAX_HEALTH);
    
    //prepare stage money text
    std::string moneyString = "Fish Points: $" + std::to_string(money);
    
    //create round text and set it
    roundText.setFont(stageFont);
    roundText.setString(roundString);
    roundText.setCharacterSize(20);
    roundText.setFillColor(Color::White);
    roundText.setPosition(TILE_SIZE, 0.0f);

    //set the stage health text
    healthText.setFont(stageFont);
    healthText.setString(healthString);
    healthText.setCharacterSize(20);
    healthText.setFillColor(Color::White);
    healthText.setPosition(TILE_SIZE, TILE_SIZE);

    //set the stage money text
    moneyText.setFont(stageFont);
    moneyText.setString(moneyString);
    moneyText.setCharacterSize(20);
    moneyText.setFillColor(Color::White);
    moneyText.setPosition(TILE_SIZE, TILE_SIZE*2);

    switch(stageState){
        case ROUND:
            roundDriver(); 
            break;
        case TOWER:
            towerDriver();
            break;
        case WIN:
            finishedDriver("WIN");
            break;
        case LOOSE:
            finishedDriver("LOOSE");
            break;
    }
}

void Stage::towerDriver(){
        //decide if the game is finished
        if(currentRound > maxRounds){
            stageState = WIN;
            return;
        }
        
        //draw the path to the screen
        drawMultipleSprites(path);

        //display the towers
        drawMultipleSprites(stageTowers);
        drawMultipleSprites(placedTowers);

        //draw the button for the next round
        window->draw(*(button->sprite));

        //draw the text
        window->draw(roundText);
        window->draw(healthText);
        window->draw(moneyText);
        
        //tower radius
        hoverTower();           
        
        for(long unsigned int i = 0; i < towerCostText.size(); ++i){
            window->draw(*towerCostText[i]);
        }

        //display the screen
        window->display();

        //if tower drag on, move the tower
        if(towerDrag){
            Vector2f mouse = window->mapPixelToCoords(Mouse::getPosition(*window));
            mouse.x -= TILE_SIZE / 2;
            mouse.y -= TILE_SIZE / 2;
            stageTowers[towerPos]->sprite->setPosition(mouse);
            bool checkPath = false;

            //check to see that the path has not been clicked
            for(long unsigned int i = 0; i < path.size(); ++i){
                checkPath |= isCollided(path[i], stageTowers[towerPos]);
            }

            //make sure the next round button is not clicked
            checkPath |= isCollided(button, stageTowers[towerPos]);

            //make sure it is not being placed on the tower selection
            for(long unsigned int i = 0; i < stageTowers.size(); ++i){
                if((int) i != towerPos)
                    checkPath |= isCollided(stageTowers[i], stageTowers[towerPos]);
            }
            
            //place the tower
            if(!checkPath && Screen::isClicked(stageTowers[towerPos]) && frame_count <= 0){
                frame_count = TILE_SIZE;
                towerDrag = false;
                
                //set tower to placedTowers vector
                placedTowers.push_back(stageTowers[towerPos]);
               
                //set the raidus of the tower 
                Vector2f rangePos = stageTowers[towerPos]->sprite->getPosition();
                rangePos.x -= TILE_SIZE * 1.5;
                rangePos.y -= TILE_SIZE * 1.5;

                std::shared_ptr<NewSprite> range = std::make_shared<NewSprite>(spriteLocation + "square.png");
                range->sprite->setPosition(rangePos);
                range->sprite->setScale(4.f, 4.f);
                placedTowerRadius.push_back(range);

                //put copy of tower into stageTowers
                stageTowers[towerPos] = std::make_shared<Tower>(stageTowers[towerPos]->spriteName,stageTowers[towerPos]->getAttack(), stageTowers[towerPos]->getCost());
                stageTowers[towerPos]->sprite->setScale(0.5f, 0.5f);
                stageTowers[towerPos]->sprite->setPosition(originalPos);
            }
            frame_count--;
        }
        //check if the button has been clicked
        else if(Screen::isClicked(button)){
            //reset enemy round vectors
            roundEnemies.clear();
            correspondingTile.clear();
            isDead.clear();

            //construct the round and start the round
            constructRound(currentRound);
            currentRound++;
            stageState = ROUND;
            frame_count = TILE_SIZE;
        }

        //loop through towers and see if any have been clicked
        for(long unsigned int i = 0; !towerDrag && i < stageTowers.size(); ++i){
            if(Screen::isClicked(stageTowers[i]) && stageTowers[i]->getCost() <= money){
                money -= stageTowers[i]->getCost();
                towerDrag = true;
                towerPos = i;
                originalPos = stageTowers[i]->sprite->getPosition();
            }
        }        
        
}

void Stage::roundDriver(){
        //draw the text
        window->draw(roundText);
        window->draw(healthText);
        window->draw(moneyText);
            
        //draw the path to the screen
        //drawMultipleSprites(path);

        //draw the towers
        drawMultipleSprites(placedTowers);

        //tower radius
        hoverTower();           
 
        //draw enemies and attacks to the screen
        drawMultipleSprites(roundEnemies);

        //display the screen
        window->display();

        //update enemy location
        moveEnemies();

        //decrement frame count (mod 32)
        frame_count--;
}

void Stage::finishedDriver(std::string finishedText){
        //place the finshed button
        finishedButton->sprite->setPosition(CENTER_X-(TILE_SIZE/2), CENTER_Y-(TILE_SIZE/2) + TILE_SIZE * 4);
    
        //finished text
        Text endText;
        endText.setFont(endFont);
        endText.setString(finishedText);
        endText.setCharacterSize(64);
        endText.setFillColor(Color::White);
        endText.setPosition(CENTER_X, CENTER_Y);
        window->draw(endText);
    
        //draw the button
        window->draw(*(finishedButton->sprite));

        if(isClicked(finishedButton)){
            *gs = MAIN_MENU;
            reset();
        }
        
        //display the window
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
            //allocate sprite
            path.push_back(std::make_shared<NewSprite>(pathSpriteLocation));

            //update position
            initial_position = calculate_position(initial_position, direction[i], 1, TILE_SIZE);

            //set position
            path[path.size()-1]->sprite->setPosition(initial_position);
            
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
    currentEnemyPos.x -= TILE_SIZE;
    int initial = -1;

    //set all sprites in the path
    for(long unsigned int i = 0; i < enemy_count.size(); ++i){
        for(int j = 0; j < enemy_count[i]; ++j){
            //set position of enemy
            roundEnemies.push_back(getEnemyType(enemy_type[i]));
            roundEnemies[roundEnemies.size()-1]->sprite->setPosition(currentEnemyPos);
            correspondingTile.push_back(initial);
            initial--;

            //allocate is dead flag
            isDead.push_back(false);

            //update position
            currentEnemyPos.x -= TILE_SIZE;
        }
    }
}

std::shared_ptr<Enemy> Stage::getEnemyType(char type){
    switch(type){
        case 'r':
            return std::make_shared<Enemy>(spriteLocation + "redFish.png", 10);
        case 'b':
            return std::make_shared<Enemy>(spriteLocation + "bossFish.png", 100);
        case 'g':
            return std::make_shared<Enemy>(spriteLocation + "greenFish.png", 20);
        case 'o':
            return std::make_shared<Enemy>(spriteLocation + "orangeFish.png", 30);
        case 'p':
            return std::make_shared<Enemy>(spriteLocation + "purpleFish.png", 40);
        default:
            return nullptr;
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

template <typename T>
void Stage::drawMultipleSprites(std::vector<std::shared_ptr<T>> vec) {
    for(long unsigned int i = 0; i < vec.size(); ++i){
        window->draw(*(vec[i]->sprite));
    }
}

void Stage::moveEnemies(){
    //std::cout << correspondingTile[(int) correspondingTile.size() - 1] << "\t" << directions.size() << std::endl;

    if(health <= 0){
        stageState = LOOSE;
        return;
    }
   
    bool end = true;

    for(long unsigned int i = 0; i < isDead.size(); ++i){
        end &= isDead[i];
    }
 
    if(end){
        stageState = TOWER;
        frame_count = TILE_SIZE;
        return;
    }

    //happens every second
    if(frame_count == 0){
        for(long unsigned int i = 0; i < roundEnemies.size(); ++i){
            correspondingTile[i] += 1;

            //check if collides with radius
            for(long unsigned int j = 0; j < placedTowerRadius.size(); ++j){
                if(isCollided(roundEnemies[i], placedTowerRadius[j])){
                    //decrease health by attack
                    roundEnemies[i]->setHealth(roundEnemies[i]->getHealth() - placedTowers[j]->getAttack());
                    
                    //set opacity based on health
                    int total = roundEnemies[i]->getHealth();
                    int current = roundEnemies[i]->getInitialHealth();
                    int opacity = ((float) total/(2*current) + 0.5) * 255;
                    roundEnemies[i]->sprite->setColor(Color(255,255,255,opacity));
                }
            }

            //check if enemy is dead, increment money, check flag
            if(!isDead[i] && roundEnemies[i]->getHealth() <= 0){
                isDead[i] = true;
                money++;
                roundEnemies[i]->sprite->setColor(Color::Transparent); 
                continue;
            }
        }

        frame_count = TILE_SIZE;
    }

    for(long unsigned int i = 0; i < roundEnemies.size(); ++i){
        //sprite has reached the end
        if((long unsigned int)correspondingTile[i] == directions.size() - 1 || isDead[i]){
            if(!isDead[i]){
                health -= roundEnemies[i]->getHealth();
                isDead[i] = true;
            }
            roundEnemies[i]->sprite->setColor(Color::Transparent); 
            continue;
        }

        //get the enemy location
        Vector2f currentEnemyPos = roundEnemies[i]->sprite->getPosition();
        
        //update position
        if(correspondingTile[i] <= 0){
            currentEnemyPos.x += 1;
        } else {
            currentEnemyPos = calculate_position(currentEnemyPos, directions[correspondingTile[i]+1], 1, 1);
        }

        //set the position
        roundEnemies[i]->sprite->setPosition(currentEnemyPos);
    }
}


template <typename T, typename U>
bool Stage::isCollided(std::shared_ptr<T> sprite1, std::shared_ptr<U> sprite2){
    FloatRect sprite1Bounds = sprite1->sprite->getGlobalBounds();
    FloatRect sprite2Bounds = sprite2->sprite->getGlobalBounds();

    return sprite1Bounds.intersects(sprite2Bounds);
}

void Stage::hoverTower(){
        Vector2f mouse = window->mapPixelToCoords(Mouse::getPosition(*window));

        for(long unsigned int i = 0; i < placedTowerRadius.size(); ++i){
            FloatRect bounds = placedTowers[i]->sprite->getGlobalBounds();
            if(bounds.contains(mouse)){
                placedTowerRadius[i]->sprite->setColor(Color(255,255,255,128));
                window->draw(*placedTowerRadius[i]->sprite);
            }
        }
}
