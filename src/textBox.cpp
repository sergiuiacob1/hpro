#include "textBox.h"
#include "misc.h"

textBox::~textBox()
{

}

sf::Font font;
bool fictiv=font.loadFromFile("fonts/arial.ttf");

textBox::textBox()
{
    active=false;
    text.setFont(font);
    text.setCharacterSize(CHARSIZE);
    text.setColor(sf::Color::Black);

    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(2);
}

bool textBox::getStatus() const
{
    return active;
}

void textBox::setStatus(const bool &status)
{
    active=status;
    if (status)
    {
        shape.setOutlineColor(sf::Color(135, 206, 250));
        shape.setOutlineThickness(4);
    }
        else
        {
            shape.setOutlineColor(sf::Color::Black);
            shape.setOutlineThickness(2);
        }
}

void textBox::setPosition (const int &val1, const int &val2)
{
    this->setX(val1); this->setY(val2);
    shape.setPosition(val1, val2);
    text.setPosition(val1, val2);
}

void textBox::setSize(const int &latime, const int &inaltime)
{
    this->setWidth(latime); this->setHeight(inaltime);
    shape.setSize(sf::Vector2f(latime, inaltime));
}

string textBox::getString() const
{
    return sir;
}

sf::Text& textBox::getText()
{
    return text;
}

sf::RectangleShape& textBox::getShape()
{
    return shape;
}

 void textBox::setString (const string &aux)
 {
    sir=aux;
    text.setString(sir);

    sf::FloatRect sizes;
    sizes=this->getText().getGlobalBounds();

    if (sizes.width>=this->getWidth()-1)//Houston, we have a problem
    {
        //caut ultimul spatiu si pun newline acolo
        int i; bool found=false;
        for (i=sir.size()-1; i>=0; --i)
            if (sir[i]==' ')
        {
            sir[i]='\n';
            found=true;
            break;
        }
            else
            if (sir[i]=='\n')
                break;

        if (!found)
            sir=sir.substr(0, sir.size()-1)+'\n'+sir[sir.size()-1];
        text.setString(sir);

        this->resizeTextBox();
    }
 }

void textBox::sterge()
{
    if (sir.size()==0)
        return;
    sir.erase(sir.size()-1, sir.size());
    text.setString(sir);

    if (sir[sir.size()-1]=='\n')
    {
        sir.erase(sir.size()-1, sir.size());
        text.setString(sir);

        this->resizeTextBox();
    }
}

void textBox::resizeTextBox()
{
    sf::FloatRect sizes;
    sizes=text.getGlobalBounds();
    this->setHeight(sizes.height+DISTANCE*2);
    this->setSize(this->getWidth(), this->getHeight());
}
