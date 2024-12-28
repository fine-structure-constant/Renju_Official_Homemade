#include "sfmlgui.h"

const float TILE_SIZE = 40.f;
sf::Color black(0, 0, 0);
sf::Color white(255, 255, 255);
sf::Color red(255, 0, 0);

Point click_to_select(sf::RenderWindow& window){
    sf::Event event;
    while (window.pollEvent(event)) {             //如果有事件。如果有多个while会排队处理
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                int x = event.mouseButton.x / TILE_SIZE;
                int y = event.mouseButton.y / TILE_SIZE;

                if (board[x][y] == 0) {
                    return Point({x,y});
                }
            }
        }
    }
    return Point({-1,-1});
}

void drawBoard(sf::RenderWindow& window,Point p0) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            // 绘制棋盘格子
            sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            tile.setPosition(i * TILE_SIZE, j * TILE_SIZE);
            tile.setFillColor(sf::Color(255, 204, 153)); // 淡黄背景色
            window.draw(tile);

            // 绘制格子边框
            sf::RectangleShape border(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            border.setPosition(i * TILE_SIZE, j * TILE_SIZE);
            border.setFillColor(sf::Color::Transparent);
            border.setOutlineColor(sf::Color::Black);
            border.setOutlineThickness(1);
            window.draw(border);

            // 绘制棋子
            if (board[i][j] == 1) { // 黑子
                sf::CircleShape piece(TILE_SIZE / 2);
                piece.setFillColor(black);
                piece.setPosition(i * TILE_SIZE  , j * TILE_SIZE );
                window.draw(piece);
            } else if (board[i][j] == 2) { // 白子
                sf::CircleShape piece(TILE_SIZE / 2);
                piece.setFillColor(white);
                piece.setPosition(i * TILE_SIZE , j * TILE_SIZE );
                window.draw(piece);
            }
            if (i==p0.x and j==p0.y) {
                sf::CircleShape piece(TILE_SIZE / 8);
                piece.setFillColor(red);
                piece.setPosition(i * TILE_SIZE , j * TILE_SIZE );
                window.draw(piece);
            }
        }
    }
}