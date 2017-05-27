#include "searchResult.h"
#include "misc.h"

searchResult::searchResult()
{
    this->getShape().setOutlineColor(sf::Color::Red);
    this->getShape().setOutlineThickness(0);
    this->getText().setCharacterSize(CHARSIZE-(4*WINDOW_HEIGHT/600));
    //ctor
}

void searchResult::setPosInHoteluri(const int &val)
{
    posInHoteluri=val;
}

int searchResult::getPosInHoteluri() const
{
    return posInHoteluri;
}

void searchResult::setCounter (const int &val)
{
    counter=val;
    if (counter%2)
        this->getShape().setFillColor(sf::Color(255, 255, 204));
        else
        this->getShape().setFillColor(sf::Color(224, 224, 224));
}

int searchResult::getCounter () const
{
    return counter;
}

void searchResult::checkHover()
{
    sf::Vector2i mousePosition=sf::Mouse::getPosition(window);

    this->getShape().setOutlineThickness(0);
    if (mouseIsInside(mousePosition, *this))
    {
        this->getShape().setOutlineColor(sf::Color(135, 206, 250));
        this->getShape().setOutlineThickness(3);
    }

    /*if (this->getX()<=mousePosition.x && mousePosition.x<=this->getX()+this->getWidth())
        if (this->getY()<=mousePosition.y && mousePosition.y<=this->getY()+this->getHeight())
        {
            this->getShape().setOutlineColor(sf::Color(135, 206, 250));
            this->getShape().setOutlineThickness(3);
        }*/
}

searchResult& searchResult::operator = (const hotel &ob)
{
    this->setCity(ob.getCity());
    this->setName(ob.getName());
    this->setDescription(ob.getDescription());

    this->setRating(ob.getRating());
    this->setSum(ob.getSum());
    this->setNrVoturi(ob.getNrVoturi());
    this->setId(ob.getId());
    return *this;
}
