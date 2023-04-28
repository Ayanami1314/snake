//
// Created by Ayanami on 2023/4/28.
//

#ifndef UNTITLED18_GRAPH_INITIALIZE_H
#define UNTITLED18_GRAPH_INITIALIZE_H
#include "all_global.h"
void initialize(graph& g,char boundary_signal='#'){
    //初始化
    snake1.len = 0;
    snake2.len = 0;
    snake1.signal = '*';
    snake2.signal = '+';
    snake1.no = 1;
    snake2.no = 2;
    int i,j;
    for(i=0;i<g.x_width+2;i++){
        g.a[0][i] = boundary_signal;
    }
    for(i=1;i<g.y_width+1;i++){
        for(j=0;j<g.x_width+2;j++) {
            if(j==0 || j==g.x_width+1) g.a[i][j] = boundary_signal;
            else g.a[i][j] =' ';
        }
    }
    for(i=0;i<g.x_width+2;i++) {
        g.a[g.y_width][i] = boundary_signal;
    }
}
void initialize2(graph& g,char boundary_signal='#'){
    //中等难度初始化
    snake1.len = 0;
    snake2.len = 0;
    snake1.signal = '*';
    snake2.signal = '+';
    snake1.no = 1;
    snake2.no = 2;
    int i,j;
    for(i=0;i<g.x_width+2;i++){
        g.a[0][i] = boundary_signal;
    }
    for(i=1;i<g.y_width+1;i++){
        for(j=0;j<g.x_width+2;j++) {
            if(j==0 || j==g.x_width+1) g.a[i][j] = boundary_signal;
            else g.a[i][j] =' ';
        }
    }
    for(i=0;i<g.x_width+2;i++){
        g.a[g.y_width][i]= boundary_signal;
    }
    for(i=5;i<=g.x_width-4;i++){
        g.a[4][i] = boundary_signal;
        g.a[g.y_width-4][i] = boundary_signal;
    }
}
void initialize3(graph& g,char boundary_signal='#'){
    //高难度初始化
    snake1.len = 0;
    snake2.len = 0;
    snake1.signal = '*';
    snake2.signal = '+';
    snake1.no = 1;
    snake2.no = 2;
    int i,j;
    for(i=0;i<g.x_width+2;i++){
        g.a[0][i] = boundary_signal;
    }
    for(i=1;i<g.y_width+1;i++){
        for(j=0;j<g.x_width+2;j++) {
            if(j==0 || j==g.x_width+1) g.a[i][j] = boundary_signal;
            else g.a[i][j] =' ';
        }
    }
    for(i=0;i<g.x_width+2;i++){
        g.a[g.y_width][i]= boundary_signal;
    }
    for(i=4;i<=8;i++){
        g.a[3][i]=boundary_signal;
        g.a[3][g.x_width-11+i]=boundary_signal;
        g.a[g.y_width-4][i]=boundary_signal;
        g.a[g.y_width-4][g.x_width-11+i]=boundary_signal;
    }
    for(j=1;j<=4;j++){
        g.a[3+j][4]=boundary_signal;
        g.a[3+j][g.x_width-3]=boundary_signal;
        g.a[g.y_width-4-j][4]=boundary_signal;
        g.a[g.y_width-4-j][g.x_width-3]=boundary_signal;
    }
}
void initialize4(graph& g,char boundary_signal='#'){
    //初始化
    snake1.len = 0;
    snake2.len = 0;
    snake1.signal = '*';
    snake2.signal = '+';
    snake1.no = 1;
    snake2.no = 2;
    int i,j;
    for(i=0;i<g.x_width+2;i++){
        g.a[0][i] = boundary_signal;
    }
    for(i=1;i<g.y_width+1;i++){
        for(j=0;j<g.x_width+2;j++) {
            if(j==0 || j==g.x_width+1) g.a[i][j] = boundary_signal;
            else g.a[i][j] =' ';
        }
    }
    for(i=0;i<g.x_width+2;i++) {
        g.a[g.y_width][i] = boundary_signal;
    }
    for(j=1;j<=g.y_width-5;j++){
        g.a[7][j]=boundary_signal;
    }
    for(j=g.y_width-1;j>=5;j--){
        g.a[g.x_width-6][j]=boundary_signal;
    }
}

void initialize5(graph& g,char boundary_signal='#'){
    //初始化
    snake1.len = 0;
    snake2.len = 0;
    snake1.signal = '*';
    snake2.signal = '+';
    snake1.no = 1;
    snake2.no = 2;
    int i,j;
    for(i=0;i<g.x_width+2;i++){
        g.a[0][i] = boundary_signal;
    }
    for(i=1;i<g.y_width+1;i++){
        for(j=0;j<g.x_width+2;j++) {
            if(j==0 || j==g.x_width+1) g.a[i][j] = boundary_signal;
            else g.a[i][j] =' ';
        }
    }
    for(i=0;i<g.x_width+2;i++) {
        g.a[g.y_width][i] = boundary_signal;
    }
    for(i=0;i<g.x_width+2;i++){
        g.a[6][i]=boundary_signal;
        g.a[g.x_width-5][i]=boundary_signal;
    }
    for(i=0;i<3;i++)
    {
        g.a[6][6+i]=' ';
        g.a[g.x_width-5][g.y_width-5+i]=' ';
    }
}
#endif //UNTITLED18_GRAPH_INITIALIZE_H
