#ifndef SFMLGUI_H
#define SFMLGUI_H
#include "Point.h"
#include "decision.h"
#include <SFML/Graphics.hpp>            //很努力地将功能分开了
extern const float TILE_SIZE;

void drawBoard(sf::RenderWindow& window,Point p0);
Point click_to_select(sf::RenderWindow& window);

#endif