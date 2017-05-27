#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <SFML/Graphics.hpp>
#include "box.h"
#include <string>
using namespace std;

class textBox: public box
{
    bool active;//true daca utilizatorul introduce text aici in momentul asta
    sf::Text text;
    sf::RectangleShape shape;
    string sir;

    public:
    textBox();
    ~textBox();
    void setPosition(const int&, const int&);
    void setSize(const int&, const int&);
    bool getStatus() const;
    void setStatus(const bool &);
    void setString (const string &);
    string getString() const;
    sf::RectangleShape& getShape();
    sf::Text& getText();
    void sterge();
    void resizeTextBox();
};

#endif // TEXTBOX_H
