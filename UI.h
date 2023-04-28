//
// Created by Ayanami on 2023/4/28.
//

#ifndef UNTITLED18_UI_H
#define UNTITLED18_UI_H
#include <iostream>
#include <random>
#include <curses.h> // 读取键盘上箭头的库
#include <deque> // 用来存储蛇身，不然没法更新蛇尾
#include <iomanip>
#include <unistd.h>
void UI_1(){

    initscr(); // 初始化PDCurses库
    mvprintw(0,0,"Once upon a time, there was a hungry snake.");
    mvprintw(1,0,"It crawled feebly in the large forest.");
    mvprintw(2,0,"Just when he felt like he was going to die,");
    mvprintw(3,0,"all of a sudden, a maze emerged in front of its eyes.");
    mvprintw(4,0,"Unbelievably, there were some apples in the maze!");
    mvprintw(5,0,"Without hesitation, it quickly started its new adventure......");
    mvprintw(7,30,"Press ant key to continue... ");
    refresh();
    getch(); // 等待用户输入
}
void UI_2(){

    mvprintw(9,0,"For you, we have designed three different modes:"); //窗口打印
    mvprintw(10,2,"1. easy   (1)");
    mvprintw(11,2,"2. medium (2)");
    mvprintw(12,2,"3. hard   (3)");
    mvprintw(13,0,"Just input the corresponding number,");
    mvprintw(14,3, "and then you can start your adventure ~~");
    mvprintw(16,1,"ps: OH!!! If you choose the hard mode, we have design");
    mvprintw(17,3,"  three different graphs for you to explore! ");
    mvprintw(18,3,"  Just have a try ~~ ");
    move(19,0);//将光标移动到下一行第一列
    refresh();
}


void UI_mode(mode& player_mode, graph& g, graph_choose& gc){

    char player_mode_num;
    bool valid_input = false;
    bool valid_input_2 = false;
    while (!valid_input) {
        player_mode_num = getch();
        switch (player_mode_num) {
            case '1':
                player_mode = easy;
                valid_input = true;
                initialize(g);
                break;
            case '2':
                player_mode = medium;
                valid_input = true;
                initialize2(g);
                break;
            case '3':
                player_mode = hard;
                valid_input = true;
                mvprintw(21, 2, "Please choose a graph to play:"); //窗口打印
                mvprintw(22, 4, "1:first, 2:second, 3:third");
                mvprintw(23, 2, "(Just press the corresponding number)");
                while (!valid_input_2) {
                    char graph_choose_num;
                    graph_choose_num = getch();
                    switch (graph_choose_num) {
                        case '1':
                            gc = fir;
                            valid_input_2 = true;
                            initialize3(g);
                            break;
                        case '2':
                            gc = sec;
                            valid_input_2 = true;
                            initialize4(g);
                            break;
                        case '3':
                            gc = thi;
                            valid_input_2 = true;
                            initialize5(g);
                            break;
                        default:
                            system("cls");
                            refresh();
                            mvprintw(0, 0, "Illegal input! Please choose mode again......");
                            mvprintw(1, 0, "Please choose a graph from 1,2,3"); //窗口打印
                            refresh();
                    }
                }
                break;

            default:
                system("cls"); // 刷新窗口
                mvprintw(0, 0, "Illegal input! Please choose mode again......");
                mvprintw(1, 0, "Please choose a mode(1:easy, 2:medium, 3:hard)"); //窗口打印
                refresh();
        }
    }
}
void UI_3(){
    mvprintw(3, 0, "All right, the adventure now begins!");
    refresh();
//sleep(3);
    clear();
    mvprintw(0, 1, "I have to briefly introduce the operation.");
    mvprintw(1, 1, "You can press these 4 keys to control your moving:");
    mvprintw(2, 3, "A & a : turn LEFT");
    mvprintw(3, 3, "D & d : turn RIGHT");
    mvprintw(4, 3, "W & w : go UP");
    mvprintw(5, 3, "S & s : go DOWN");
    mvprintw(6, 1, "If you press a key repeatedly, then you can accelerate.");
    mvprintw(8, 1, "Now you can press any key I mentioned above to start your game ~~");
    refresh();
}
#endif //UNTITLED18_UI_H
