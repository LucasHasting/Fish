#ifndef STAGE_H
#define STAGE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

class Screen{
    protected:
        std::string spriteLocation = "sprites/";
    public:
        virtual void driver(std::shared_ptr<sf::RenderWindow>) = 0;
        virtual ~Screen() = default;
};

#endif
