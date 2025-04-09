#include "../class_headers/Tower.h"

Tower::Tower(std::string sn, int attack, int cost) : NewSprite(sn){
    this->attack = attack;
    this->cost = cost;
}

int Tower::getAttack(){
    return attack;
}

int Tower::getCost(){
    return cost;
}
