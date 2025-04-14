#include "../class_headers/Enemy.h"

//constructs the enemy class
Enemy::Enemy(std::string sn, int health) : NewSprite(sn){
    this->health = health;
    this->initialHealth = health;
}

//set the health of the enemy
void Enemy::setHealth(int health){
    this->health = health;
}

//get the health of the enemy
int Enemy::getHealth(){
    return health;
}

//get the original health value of the enemy
int Enemy::getInitialHealth(){
    return initialHealth;
}
