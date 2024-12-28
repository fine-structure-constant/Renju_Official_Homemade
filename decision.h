#ifndef DECISION_H
#define DECISION_H           
#define MAX_DEPTH 2
#include "Point.h"   


using namespace std;
extern int board[BOARD_SIZE][BOARD_SIZE];    //decision的源文件中定义了一个可访问的棋盘，其它都受到保护
Point decision_shell(int whom,int r);                
bool regulate_player(Point pi);
bool judge(Point tp);   //判断当前局面是否有连成五子

#endif // DECISION_H
