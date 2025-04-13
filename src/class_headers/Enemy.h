#ifndef ENEMY_H
#define ENEMY_H

#include "NewSprite.h"
#include <string>

class Enemy : public NewSprite{
    private:
        int health;
        int initialHealth;
    public:
        Enemy(std::string sn) : NewSprite(sn) {};
        Enemy(std::string, int);
        void setHealth(int);
        int getHealth();
        int getInitialHealth();
};

#endif
