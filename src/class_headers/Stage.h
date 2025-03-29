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

using namespace sf;

class Stage : public Screen{
    private:
        std::shared_ptr<NewSprite> pathSprite = nullptr;
        std::string pathLocation = "paths/";
        std::string enemyLocation = "rounds/";
        std::string pathSpriteLocation = spriteLocation; 
        std::string pathFileLocation = pathLocation; 
        std::string enemyFileLocation = enemyLocation;
        int frame_count = TILE_SIZE * FRAME_SHIFT;
        std::vector<char> directions;
        std::vector<std::shared_ptr<NewSprite>> path;
        std::vector<std::shared_ptr<Enemy>> roundEnemies;
        std::vector<int> correspondingTile;
    public:
        Stage(std::string, std::string, std::string);
        void driver(std::shared_ptr<sf::RenderWindow>) override;
        void constructPath();
        void constructRound();
        Vector2f calculate_position(Vector2f, char, int, int);
        void drawPath(std::shared_ptr<sf::RenderWindow>);
        void drawEnemies(std::shared_ptr<sf::RenderWindow>);
        std::string getEnemyType(char);
        void moveEnemies();
};

#endif
