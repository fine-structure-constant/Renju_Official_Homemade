#include "decision.h"  // Include the decision-making library
//#include "sfmlgui.cpp"  //要是直接引用cpp连task都不用改
#include "Point.h"   //其实已经包含了这个
#include <conio.h>
#include "sfmlgui.h"
int player,anti;   //棋盘黑1白2,0为空位,执黑为0，执白为1,rd为轮数S
int rd;
Point p0,tp;
int main() {
    printf("select black(0) or white(1):");
    scanf("%d",&player);
    anti = 1 - player;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;      //抗锯齿关闭
    sf::RenderWindow window(sf::VideoMode(BOARD_SIZE * TILE_SIZE, BOARD_SIZE * TILE_SIZE), "Gomoku", sf::Style::Default, settings);
    while (1) {
        if(!window.isOpen()) break;  
        if (rd % 2 == player) {
            p0=click_to_select(window);
            if(!p0.spill() && p0(board)==0) {
                p0(board) = player+1;
                rd++;
                tp = p0;
            }
        } else {
            printf("\nAI in decision making...\n");
            p0 = decision_shell(anti,rd);
            printf("AI selected: %d , %d\n", p0.x, p0.y);
            p0(board) = anti + 1;
            rd++;
            tp = p0;
        }
        window.clear(sf::Color::White);
        drawBoard(window,tp);
        window.display();
        if (judge(tp)) {
            if (rd % 2 == anti)
                printf("player wins!");
            else
                printf("AI wins");
            printf("\nPress any key to exit...");
            _getch();
            break;
        }
    }
    return 0;
}
