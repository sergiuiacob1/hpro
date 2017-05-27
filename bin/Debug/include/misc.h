#ifndef MISC_H
#define MISC_H

#include <SFML/Graphics.hpp>
#include "imagine.h"
#include "textBox.h"
#include "hotel.h"
#include "box.h"
#include "searchResult.h"
#include "rezervare.h"
#include "user.h"

#include <cstring>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define DISTANCE 10
#define CHARSIZE (WINDOW_HEIGHT*24)/600
using namespace std;

void checkUserData();
void startApp();
template <typename T>
bool mouseIsInside (const sf::Vector2i &, const T&);
void drawScreen();
void checkMousePress(const sf::Event &);
void checkKeyPress(const sf::Event &);
void checkScroll(const sf::Event &);
void checkDataChange();

extern sf::RenderWindow window;

#endif // MISC_H
