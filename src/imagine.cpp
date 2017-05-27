#include "imagine.h"

imagine::imagine()
{
    texture.setSmooth(true);
    //ctor
}

void imagine::loadImage(const char* sir)
{
    texture.loadFromFile (sir);
    texture.setSmooth(true);
    sprite.setTexture (texture);

    this->setWidth(sprite.getGlobalBounds().width);
    this->setHeight(sprite.getGlobalBounds().height);
}

sf::Texture& imagine::getTexture()
{
    return texture;
}

sf::Sprite& imagine::getSprite()
{
    return sprite;
}

void imagine::setPosition (const int &val1, const int &val2)
{
    this->setX(val1); this->setY(val2);
    sprite.setPosition (val1, val2);
}
