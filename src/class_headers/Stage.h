#ifndef STAGE1_H
#define STAGE1_H

#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <vector>
#include <string>
#include "NewSprite.h"
#include "Enemy.h"
#include "Screen.h"
#include "GameConstants.h"
#include "StageStates.h"

using namespace sf;

class Stage : public Screen{
    private:
        enum StageStates stageState;
        int maxRounds = 0;
        bool needsConstruction = true;
        std::shared_ptr<NewSprite> pathSprite = nullptr;
        std::shared_ptr<NewSprite> button = nullptr;
        std::string pathLocation = "paths/";
        std::string enemyLocation = "rounds/";
        std::string pathSpriteLocation = spriteLocation; 
        std::string pathFileLocation = pathLocation; 
        std::string enemyFileLocation = enemyLocation;
        int frame_count = TILE_SIZE;
        std::vector<char> directions;
        std::vector<std::shared_ptr<NewSprite>> path;
        std::vector<std::shared_ptr<Enemy>> roundEnemies;
        std::vector<int> correspondingTile;
    public:
        Stage(std::string, std::string, std::string, int);
        void driver(std::shared_ptr<sf::RenderWindow>) override;
        void constructPath();
        void constructRound();
        Vector2f calculate_position(Vector2f, char, int, int);
        void drawPath(std::shared_ptr<sf::RenderWindow>);
        void drawEnemies(std::shared_ptr<sf::RenderWindow>);
        std::string getEnemyType(char);
        void moveEnemies();
        bool isButtonClicked(std::shared_ptr<sf::RenderWindow>);
};

#endif
