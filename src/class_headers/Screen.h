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
        virtual void driver(std::shared_ptr<RenderWindow>) = 0;
        virtual ~Screen() = default;

        //method to set the game state address
        void setGameState(enum GameStates* ns){
            gs = ns;
        }
    protected:
        std::string spriteLocation = "sprites/";
        std::shared_ptr<RenderWindow> window;
        enum GameStates* gs;

        //templated isClicked method used in all children classes 
        //to tell if a sprite has been clicked by the mouse
        template <typename T>
        bool isClicked(std::shared_ptr<T> sprite){
            
            //if the left mouse has been clicked
            if(Mouse::isButtonPressed(Mouse::Left)){
                //return true if the mouse is in the bounds of the sprite, false otherwise
                Vector2f mouse = window->mapPixelToCoords(Mouse::getPosition(*window));
                FloatRect bounds = sprite->sprite->getGlobalBounds();
                return bounds.contains(mouse);         
            }

            //the mouse has not been clicked
            return false;
        }
};

#endif
