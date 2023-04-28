//
// Created by Ayanami on 2023/4/28.
//

#ifndef UNTITLED18_SCORE_TIME_H
#define UNTITLED18_SCORE_TIME_H
#include <ctime>
#include "snake&graph.h"
#include <curses.h> // 读取键盘上箭头的库
#include <deque> // 用来存储蛇身，不然没法更新蛇尾
#include <iomanip>
#include <unistd.h>
#include "all_global.h"
#include <string>
int cur_time = 60;
int count_time(clock_t& board_start_time){
    //倒计时ts
    clock_t now_time = clock();
    cur_time = 60- int((now_time-board_start_time)/CLOCKS_PER_SEC);
    return cur_time;
}
int score1(clock_t ctime){
    double rate = 0.1;//存活时间分数折算率
    return snake1.len+ rate*(60-cur_time);
}
const char* int_to_string(int a){
    std::string s="";
    while(a>0){
        s+=a%10+'0';
        a/=10;
    }
    std::string rev_s="";
    for(int i=s.length()-1;i>=0;i--){
        rev_s += s[i];
    }
    const char* c = rev_s.c_str();
    return c;
}
void pointboard(snake&s1, snake&s2,clock_t ctime){
    //计分板，在地图上方输出
    mvprintw(0,0,"-------------------Time-----------------");
    mvprintw(1,20, "%s",int_to_string(count_time(ctime)));
    mvprintw(2,0,"----------------PointBoard--------------");
    mvprintw(3,0,"Score:%d",score1(ctime));
    mvprintw(5,0,"-----------------Snake------------------------");
    refresh();
    move(6,0);
}


#endif //UNTITLED18_SCORE_TIME_H
