#include "include/misc.h"

int main()
{
    sf::Event event;
    checkUserData();
    startApp();

    while (window.isOpen())
    {
        drawScreen();
        while (window.pollEvent(event))
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                        else
                        checkScroll(event);
                        break;

                case sf::Event::MouseButtonPressed:
                    checkMousePress(event);
                    break;

                case sf::Event::TextEntered:
                    checkKeyPress(event);
                    break;

                /*case sf::Event::MouseWheelScrolled:
                    checkScroll(event);
                    break;*/

                default:
                    break;
            }
    }

    checkDataChange();
    return 0;
}
