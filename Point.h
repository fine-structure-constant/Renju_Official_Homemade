#ifndef POINT_H
#define POINT_H

#define BOARD_SIZE 15
#include <utility>
//这是一个点的数据类型，支持多种操作。点基于棋盘，故定义了BOARD_SIZE
using namespace std;

struct Point{    //定义点，支持加减，访问，数组赋值
    int x,y;
    Point(int x=0,int y=0) :x(x),y(y){}
    Point operator+(const Point other){
        return Point(x+other.x,y+other.y);
    }
    Point operator+(pair<int,int> other){

        return Point(x+other.first,y+other.second);
    }
    Point operator-(pair<int,int> other){
        return Point(x-other.first,y-other.second);
    }
    int& operator()(int arr[BOARD_SIZE][BOARD_SIZE]) {
        return arr[x][y]; // 根据 Point(x, y) 返回对应的数组元素
    }
    inline bool spill(){
        if (x<0 ||x>=BOARD_SIZE||y<0||y>=BOARD_SIZE) return true;
        return false;
    }
    void set(int xx,int yy){
        x=xx;y=yy;
        return;
    }
};

#endif 
