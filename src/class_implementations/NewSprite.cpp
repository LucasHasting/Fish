#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <string>
#include "../class_headers/NewSprite.h"

using namespace sf;

NewSprite::NewSprite(std::string spriteName){    
    //Texture and Sprite declarations
    texture = std::make_shared<Texture>();
    if(!(texture->loadFromFile(spriteName))) {
        exit(1);
    }

    sprite = std::make_unique<Sprite>(*(texture));
}
