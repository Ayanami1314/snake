#ifndef UNTITLED18_APPLE_H
#define UNTITLED18_APPLE_H
#include "all_global.h"
bool isapple(graph& g,int x,int y,char apple_signal='o'){// apple_signal 按后续函数实现改
    return g.a[x][y]==apple_signal;
}
bool is_out_of_range(int x,int y,graph& g){
    //move针对碰撞做了一些特化（现已经不用），正常的越界（苹果用）用这个
    return  x<1 || x>g.x_width || y<1 || y>g.y_width; //注意这里包括墙壁，为了处理碰撞的情况
}
bool apple_pos_is_legal(int x, int y, graph& g,char boundary_signal = '#'){
    // 判断生成苹果坐标是否合法,合法：不越界、不在蛇身上
    return !is_out_of_range(x,y,g) && g.a[x][y]!=snake1.signal && g.a[x][y]!=snake2.signal && g.a[x][y]!=boundary_signal;
}

int apple_generate(mode player_mode){
    int apple_generate_time;
    switch(player_mode){
        case hard:
            apple_generate_time = 5;
            break;
        case medium:
            apple_generate_time = 5+rand()%4;//每2-8s钟刷新苹果
            break;
        case easy:
            apple_generate_time = 10;//每20s钟刷新苹果
            break;
    }
    return apple_generate_time;
}
point random_generate_apple(graph& g,char apple_signal='o',char signal_1='*',char signal_2='+'){
    int x,y;
    do{
        srand(time(NULL)); //随机数种子
        x = rand()%g.x_width+1; //产生一个1到x_width的随机整数
        y = rand()%g.y_width+1; //产生一个1到y_width的随机整数
    }while(!apple_pos_is_legal(x,y,g));
    //如果坐标不合法，重新生成坐标
    g.a[x][y]=apple_signal;
    point apple = {x,y};
    return apple;
}
bool find_apple(const graph& g, char apple_signal = 'o'){
    // 试图寻找apple, 如果地图里面没有apple了，那就立刻重新生成
    int i,j;
    bool flag=false;
    for(i=0;i<g.x_width+2;i++){
        for(j=0;j<g.y_width+2;j++){
            if(g.a[i][j]==apple_signal){
                flag=true;
                break;
            }
        }
    }
    return flag;
}
#endif