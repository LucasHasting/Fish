#ifndef TOWER_H
#define TOWER_H

#include "NewSprite.h"
#include <string>

class Tower : public NewSprite{
    private:
        int attack;
        int cost;
    public:
        Tower(std::string sn) : NewSprite(sn) {};
        Tower(std::string, int, int);
        int getAttack();
        int getCost();
};

#endif
