#include "../class_headers/Tower.h"

//constructs the tower class
Tower::Tower(std::string sn, int attack, int cost) : NewSprite(sn){
    this->attack = attack;
    this->cost = cost;
}

//get the attack of the tower
int Tower::getAttack(){
    return attack;
}

//get the cost of the tower
int Tower::getCost(){
    return cost;
}
