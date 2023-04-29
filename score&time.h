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
#include <fstream>
#include <thread>
#include <chrono>

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
    //把一个数变成字符串，然后可以mvprintw输出
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

int readHighScore(){
    //读取并且打印历史最高数据的函数
    static int highScore = 0;
    std::ifstream file;
    file.open("highscore.txt", std::ifstream::in);
    if (file.good())
    {
        file >> highScore;
    }
    file.close();

    return highScore;

}
// 写入新的历史最高分
void writeHighScore(int score)
{
    std::ofstream file("highscore.txt", std::ios::out | std::ios::trunc);
    if (file.good())
    {
        file << score << std::endl;
    }
    file.close();
}


void pointboard(snake&s1, clock_t ctime){
    //计分板，在地图上方输出
    mvprintw(0,0,"-------------------Time-----------------");
    mvprintw(1,20, "%s",int_to_string(count_time(ctime)));
    mvprintw(2,0,"----------------PointBoard--------------");
    mvprintw(3,0,"Score:%d",score1(ctime));
    int highScore = readHighScore();//记录最高分
    mvprintw(3,10,"highest record:%d",highScore);
    mvprintw(5,0,"-----------------Snake------------------------");
    refresh();
    move(6,0);
}
void printword(graph& g,point& next_loc){
    //用于蛇在吃到果子时打印“great”和“excellent”“awesome”等,蛇每动一下都要调用这个函数
    static int num=0;//记录吃到果子的次数
    if(g.a[next_loc.x][next_loc.y]=='o'){
        num++;
        switch(num%3){
            case 0: mvprintw(10+num,25,"great!");break;
            case 1: mvprintw(10+num,25,"excellent!");break;
            case 2: mvprintw(10+num,25,"awesome!");break;
        }
        refresh();

    }
}


#endif //UNTITLED18_SCORE_TIME_H
