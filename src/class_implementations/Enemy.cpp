#include "../class_headers/Enemy.h"

Enemy::Enemy(std::string sn, int health) : NewSprite(sn){
    this->health = health;
    this->initialHealth = health;
}

void Enemy::setHealth(int health){
    this->health = health;
}

int Enemy::getHealth(){
    return health;
}

int Enemy::getInitialHealth(){
    return initialHealth;
}
