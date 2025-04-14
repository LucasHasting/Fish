#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <string>
#include "../class_headers/NewSprite.h"

using namespace sf;

NewSprite::NewSprite(std::string spriteName){    
    //save the sprite file in the object
    this->spriteName = spriteName;

    //load texture from the file
    texture = std::make_shared<Texture>();
    if(!(texture->loadFromFile(spriteName))) {
        exit(1);
    }

    //save the sprite with the texture
    sprite = std::make_unique<Sprite>(*(texture));
}
