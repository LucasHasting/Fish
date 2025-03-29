#ifndef ENEMY_H
#define ENEMY_H

#include "NewSprite.h"
#include <string>

class Enemy : public NewSprite{
    private:
        int health;
        int rate;
    public:
        Enemy(std::string sn) : NewSprite(sn) {};
        Enemy(std::string, int, int);
        void setHealth(int);
        int getHealth();
        int getRate();
};

#endif
