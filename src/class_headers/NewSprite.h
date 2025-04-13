#ifndef NEW_SPRITE_H
#define NEW_SPRITE_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

using namespace sf;

class NewSprite{
    public:
        std::shared_ptr<Sprite> sprite;
        std::shared_ptr<Texture> texture;
        std::string spriteName;
        NewSprite(std::string);
};

#endif
