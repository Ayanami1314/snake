//
// Created by Ayanami on 2023/4/28.
//

#ifndef UNTITLED18_SNAKE_GRAPH_H
#define UNTITLED18_SNAKE_GRAPH_H
#include <deque>
#include "score&time.h"
#include "all_global.h"
#include "apple.h"
step get_next_step_no1(char input) {
    // 此函数接收用户键盘输入
    // no: 1 or 2, 蛇的编号
    // input: 对1号蛇，是WASD，对2号蛇是↑←↓→
    step next;
    //1号玩家，wasd
    switch (input) {
        case 'w':
            next.x = next_step[0][0];
            next.y = next_step[0][1];
            break;
        case 'W':
            next.x = next_step[0][0];
            next.y = next_step[0][1];
            break; // 不区分大小写
        case 's':
            next.x = next_step[1][0];
            next.y = next_step[1][1];
            break;
        case 'S':
            next.x = next_step[1][0];
            next.y = next_step[1][1];
            break;
        case 'a':
            next.x = next_step[2][0];
            next.y = next_step[2][1];
            break;
        case 'A':
            next.x = next_step[2][0];
            next.y = next_step[2][1];
            break;
        case 'd':
            next.x = next_step[3][0];
            next.y = next_step[3][1];
            break;
        case 'D':
            next.x = next_step[3][0];
            next.y = next_step[3][1];
            break;
        default:
            break;
    }
    return next;
}
step get_next_step_no2(char input){
    // 键盘读取2号玩家，↑←↓→的移动

    char ch;
    step next;
    if(int(input) == 224 || int(input) == 0){
        ch = getch(); // 读取第二个字符,读箭头的特殊方法，箭头是由两个字符组成的，第一个是0/224的标记符
        switch (ch) {
            case 72: // 上箭头
                next.x = next_step[0][0];
                next.y = next_step[0][1];
                break;
            case 80: // 下箭头
                next.x = next_step[1][0];
                next.y = next_step[1][1];
                break;
            case 75: // 左箭头
                next.x = next_step[2][0];
                next.y = next_step[2][1];
                break;
            case 77: // 右箭头
                next.x = next_step[3][0];
                next.y = next_step[3][1];
                break;
            default:
                break;
        }
    }
    return next;
}
bool snake_is_collision(graph&g, snake& s, char special_signal = ' '){
    //头在x,y=0/width+1 时碰撞
    int x = s.head.x;
    int y = s.head.y;
    if(x==0 || x==g.x_width+1 || y==0 || y==g.y_width+1) return true;

    if(special_signal=='?'){
        return true;
    }
    return false;
}
bool move_is_out_of_range(int x,int y,graph& g){
    // 判断坐标x,y 是否越界, 初版用的碰撞
    return  x<0 || x>g.x_width+1 || y<0 || y>g.y_width+1; //注意这里包括墙壁，为了处理碰撞的情况
}

void print(graph& g,char boundary_signal='#'){
    /* 打印整个地图，每隔timestep 秒更新一次（在main中用clock()函数计算时间和清屏（system("cls")）实现）
     */
    // a 的 大小应该是x_width+2,y_width+2, 边界符号#
    // 实际过程中，蛇的坐标都应该从1开始计数，0是边界
    int i,j;
//    for(i=0;i<g.x_width+2;i++){
//        for(j=0;j<g.y_width+2;j++){
//            putchar(g.a[i][j]); //实时输出
//        }
//        putchar('\n'); //换行
//    }
    int row=6,col=0;
    move(6,0);
//    getyx(stdscr, row, col); // 获取光标位置

    for(i=0;i<g.x_width+2;i++){
        char * c_s = g.a[i];
        c_s[g.y_width+2] = '\0';  // 这里给地图最后加上一个'\0'，使得mvprintw能够正常结束，不出现乱码
        mvprintw(row+i,col,c_s);
        refresh();
    }
    move(0,0);
}

void snake_begin(graph& g,int no,int begin_x,int begin_y){
    //  在begin_x,begin_y坐标 ,产生一条为no = 1 or 2 的蛇
    if(no==1){
        snake1.len=1;
        snake1.head.x = begin_x;
        snake1.head.y = begin_y;
        snake1.tail.x = begin_x;
        snake1.tail.y = begin_y;
        g.a[begin_x][begin_y] = snake1.signal;
        snake1.body.push_back(snake1.head);
    }

    if(no==2){
        snake2.len=1;
        snake2.head.x = begin_x;
        snake2.head.y = begin_y;
        snake2.tail.x = begin_x;
        snake2.tail.y = begin_y;
        g.a[begin_x][begin_y] = snake2.signal;
        snake2.body.push_back(snake2.head);
    }
}



#endif //UNTITLED18_SNAKE_GRAPH_H
