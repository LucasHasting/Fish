#include "../class_headers/Enemy.h"

Enemy::Enemy(std::string sn, int health, int rate) : NewSprite(sn){
    this->health = health;
    this->initialHealth = health;
    this->rate = rate;
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

int Enemy::getRate(){
    return rate;
}
