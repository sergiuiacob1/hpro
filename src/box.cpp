#include "box.h"

int box::getX() const
{
    return x;
}

int box::getY() const
{
    return y;
}

int box::getWidth() const
{
    return width;
}

int box::getHeight() const
{
    return height;
}

void box::setX(const int &val)
{
    x=val;
}

void box::setY(const int &val)
{
    y=val;
}

void box::setWidth(const int &val)
{
    width=val;
}

void box::setHeight(const int &val)
{
    height=val;
}

