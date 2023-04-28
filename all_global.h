//
// Created by Ayanami on 2023/4/28.
//

#ifndef UNTITLED18_ALL_GLOBAL_H
#define UNTITLED18_ALL_GLOBAL_H
#include "deque"
extern int cur_time;
int next_step[4][2]={{-1,0},{1,0},{0,-1},{0,1}};//上下左右（wsad）
struct point{
    int x;
    int y;
};
struct graph{
    char a[101][101]; // 地图
    int x_width; // x宽
    int y_width; // y宽
};

struct snake{
    int no;
    int len;
    point head;
    point tail;
    std::deque<point> body;
    char signal;
};
struct snake snake1,snake2;
struct step{
    int x;
    int y;
};
enum mode{
    easy,
    medium,
    hard
};
enum graph_choose{
    fir,
    sec,
    thi
};
#endif //UNTITLED18_ALL_GLOBAL_H
