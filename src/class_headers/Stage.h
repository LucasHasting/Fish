#ifndef STAGE_H
#define STAGE_H

#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <vector>
#include <string>
#include "NewSprite.h"
#include "Enemy.h"
#include "Tower.h"
#include "Screen.h"
#include "GameConstants.h"
#include "StageStates.h"

using namespace sf;

class Stage : public Screen{
    private:
        Font endFont;
        Font stageFont;
        Text roundText;
        Text healthText;
        Text moneyText;
        enum StageStates stageState;
        bool needsConstruction = true;
        bool towerDrag = false;
        int towerPos = -1;
        int maxRounds = 0;
        int currentRound = 0;
        int frame_count = TILE_SIZE;
        int health = MAX_HEALTH;
        int money = STARTING_AMOUNT;
        std::string pathLocation = "paths/";
        std::string enemyLocation = "rounds/";
        std::string pathSpriteLocation = spriteLocation; 
        std::string backgroundSpriteLocation = spriteLocation; 
        std::string pathFileLocation = pathLocation; 
        std::string enemyFileLocation = enemyLocation;
        std::shared_ptr<NewSprite> button = nullptr;
        std::shared_ptr<NewSprite> finishedButton = nullptr;
        std::shared_ptr<NewSprite> pathSprite = nullptr;
        std::shared_ptr<NewSprite> background = nullptr;
        std::vector<char> directions;
        std::vector<std::shared_ptr<NewSprite>> path;
        std::vector<std::shared_ptr<Enemy>> roundEnemies;
        std::vector<std::shared_ptr<Tower>> stageTowers;
        std::vector<std::shared_ptr<Tower>> placedTowers;
        std::vector<std::shared_ptr<NewSprite>> placedTowerRadius;
        std::vector<int> correspondingTile;
        std::vector<std::shared_ptr<Text>> towerCostText;
        std::vector<bool> isDead;
        Vector2f originalPos;
        void reset();
        void moveEnemies();
        void constructPath();
        void constructTowers();
        void constructRound(int);
        void towerDriver();
        void roundDriver();
        void finishedDriver(std::string);
        void hoverTower();
        std::shared_ptr<Enemy> getEnemyType(char);
        Vector2f calculate_position(Vector2f, char, int, int);
        
        template <typename T>
        void drawMultipleSprites(std::vector<std::shared_ptr<T>>);

        template <typename T, typename U>
        bool isCollided(std::shared_ptr<T> sprite1, std::shared_ptr<U> sprite2);
    public:
        Stage(std::string, int, std::string);
        void driver(std::shared_ptr<sf::RenderWindow>) override;
};

#endif
