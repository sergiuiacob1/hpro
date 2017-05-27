#ifndef IMAGINE_H
#define IMAGINE_H
#include <SFML/Graphics.hpp>
#include "box.h"


class imagine: public box
{
    sf::Texture texture;
    sf::Sprite sprite;

    public:
    imagine();
    void loadImage(const char*);
    sf::Texture& getTexture();
    sf::Sprite& getSprite();
    void setPosition(const int&, const int&);
};

#endif // IMAGE_H
