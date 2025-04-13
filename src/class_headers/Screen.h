#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <unistd.h>
#include <iostream>
#include "NewSprite.h"
#include "GameStates.h"
#include "GameConstants.h"

class Screen{
    public:
        virtual void driver(std::shared_ptr<sf::RenderWindow>) = 0;
        virtual ~Screen() = default;
    public:
        //method to change state
        void setGameState(enum GameStates* ns){
            gs = ns;
        }
    protected:
        std::string spriteLocation = "sprites/";
        std::shared_ptr<sf::RenderWindow> window;
        enum GameStates* gs;

        //templated isClicked method used in all children classes
        template <typename T>
        bool isClicked(std::shared_ptr<T> sprite){
            if(Mouse::isButtonPressed(Mouse::Left)){
                Vector2f mouse = window->mapPixelToCoords(Mouse::getPosition(*window));

                FloatRect bounds = sprite->sprite->getGlobalBounds();
                
                return bounds.contains(mouse);         
            }
            return false;
        }

};

#endif
