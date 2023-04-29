#include <iostream>

#include <random>
#include <curses.h> // 读取键盘上箭头的库
#include <deque> // 用来存储蛇身，不然没法更新蛇尾
#include <iomanip>
#include <unistd.h>
#include "cstdlib"
#include "snake&graph.h"
#include "graph_initialize.h"
#include "all_global.h"
#include "score&time.h"
#include "apple.h"
#include "UI.h"
using namespace std;
// 这是一个贪吃蛇程序，需要注意的是，因为用到了非标准库（windows的conio.h）以处理键盘输入
// 在clion上运行需要一特殊操作(因为clion不支持conio.h)
// 1.将<conio.h> 替换为 <curses.h>。然后根据平台的不同，将 _getch() 函数替换为 getch() 函数（如之前的回答所述）。
//
// 2.在 CMakeLists.txt 文件中添加 curses 库。在文件中找到 target_link_libraries 一行，将其更改为如下内容：
//    target_link_libraries(${PROJECT_NAME} PRIVATE curses)
// 在visual studio 里面可以直接运行

void winner(graph& g,snake& s1,clock_t ctime,char special_control_signal=' '){
    //单个玩家的时候，如果时间清零，则输出分数
    //如果撞墙，则同二玩家
    int currentScore =score1(ctime);
    int highScore = readHighScore();
    static int break_flag = 0; //判断这局游戏有没有打破记录
    if (currentScore > highScore)
    {
        highScore = currentScore;
        mvprintw(4,0,"######Congratulations,you have beaten the highest record!######");
        writeHighScore(highScore);
        refresh();
        break_flag = 1;
    }
    if(cur_time<=0){
        system("cls");
        mvprintw(1,0,"SUCH A HIGH-END ORERATION!");
        mvprintw(2,0,"It's hard to imagine how you accomplish it!");
        mvprintw(3,0,"You got score %d !",score1(ctime));
        refresh();
        system("pause"); //停住
    }
    else{
        if(snake_is_collision(g,s1,special_control_signal)){
            system("cls");
            if(break_flag){
                system("cls");
                mvprintw(1,0,"SUCH A HIGH-END ORERATION!");
                mvprintw(2,0,"It's hard to imagine how you accomplish it!");
                mvprintw(3,0,"You got score %d !",score1(ctime));
                refresh();
                system("pause");
            }
            else{
                mvprintw(1,0,"Game over!");
                mvprintw(2,0, "Unfortunately......");
                mvprintw(3,0,"You hit the wall!");
                mvprintw(4,0,"You got score: %d !",score1(ctime));
                mvprintw(5,5,"......What a pity!");
                mvprintw(6,0,"But that's OK, you can try again~ ");
                refresh();
                system("pause");
            }
        }
    }
}
void snake_moving(graph& g,snake& s, step next,char boudary_signal='#'){
    int next_x = s.head.x+next.x;
    int next_y = s.head.y+next.y;
    // 更新蛇头的坐标
    if(move_is_out_of_range(next_x,next_y,g)){
        winner(g,s,(60-cur_time)*CLOCKS_PER_SEC,'?');
        refresh();
        return;
    }
    if(g.a[next_x][next_y]==boudary_signal){
        winner(g,s,(60-cur_time)*CLOCKS_PER_SEC,'?');
        refresh();
        return;
    }
    static int flag = 1; // 判断位置是否发生变化，一次变化只更新一次printword
    if(flag){
        point next_loc;
        next_loc.x = next_x;
        next_loc.y = next_y;
        printword(g, next_loc);
        refresh();
        flag = 0;
    }
    // 更新头部
    s.head.x = next_x;
    s.head.y = next_y;
    s.body.push_back(s.head);

    // 更新地图

    // 更新蛇尾
    if(!isapple(g,next_x,next_y)){
        //清除尾部
        g.a[s.tail.x][s.tail.y] = ' ';
        s.body.pop_front();//删除原来的蛇尾
        s.tail = snake1.body[0];//蛇尾的起始位置
    }
    else{
        //蛇伸长1
        g.a[s.tail.x][s.tail.y] = s.signal;
        s.len++;
    }
    g.a[next_x][next_y]=s.signal;// 先判断再更新地图
    flag = 1; // 更新过位置的标志
}
bool if_backward(char pre_input, char input){
    if(pre_input == 'w' && input == 's') return true;
    if(pre_input == 's' && input == 'w') return true;
    if(pre_input == 'd' && input == 'a') return true;
    if(pre_input == 'S' && input == 'W') return true;
    if(pre_input == 'D' && input == 'A') return true;
    if(pre_input == 'a' && input == 'd') return true;
    if(pre_input == 'W' && input == 'S') return true;
    if(pre_input == 'A' && input == 'D') return true;
    return false;
}
void auto_snake_moving(graph&g,snake&s,char ch_for_direction,clock_t& start_time,clock_t& board_start_time,int player_no=1,double delta_t = 0.5){
    // 贪吃蛇需要有自动移动的部分
    // delta_t：移动一格动作时间间隔，单位s
    // 自动移动部分应在移动完成后自动执行

    clock_t now = clock();
    step auto_next;
    switch(player_no){
        case 1:auto_next = get_next_step_no1(ch_for_direction);break;

        default: return;
    }
    if(double(now - start_time)/CLOCKS_PER_SEC >= delta_t){ // 别忘记除CLOCKS_PER_SEC
        clear();
        snake_moving(g,s,auto_next);
        pointboard(snake1,board_start_time);
        refresh();
        move(6,0);
        print(g);
        refresh();
        move(0,0);
        start_time = now;
    }
}

int main() {


    int x_width = 20;
    int y_width = 20;
    double time_step = 1.0/60.0; // 60fps
    mode player_mode; //难度
    graph_choose gc;  // 地图选择，仅限困难模式
    graph g;
    g.x_width = x_width;
    g.y_width = y_width;
    int i, j;
    for (i = 0; i < x_width + 2; i++) {
        for (j = 0; j < y_width + 2; j++) {
            g.a[i][j] = ' ';
        }
    }

    UI_1();
    UI_2();
    UI_mode(player_mode,g,gc);
    UI_3();
    snake_begin(g, 1, 10, 10);
    char start = getch();
    int apple_generate_time = apple_generate(player_mode);
    char pre_input = start;
    char ch=pre_input;
//char start = 'W';
    step pre_direction = get_next_step_no1(start); //上一次的方向
    point first_apple = random_generate_apple(g);
    point last_apple = first_apple;
// 这里到时候要加2蛇
    auto start_time = clock();
    auto board_start_time = clock();
    auto start_apple_time = clock();// 专门的苹果计时
    auto moving_time = clock(); //用于自动移动计算时间
    noecho(); //禁止输入回显
    curs_set(0);//不显示光标
    keypad(stdscr, TRUE); // 获取键值
// 这里再nodelay
    nodelay(stdscr, TRUE);// 非阻塞模式,一定要开，否则getch()函数会暂停控制台输出
//    pointboard(snake1,snake2,start_time);
//    print(g);
//    move(0,0);}
    while (true) {
        if(ch!=ERR) pre_input = ch;
        clock_t current_time = clock();
        double elapsed_time = (double) (current_time - start_time) / CLOCKS_PER_SEC;
        double elapsed_apple_time = (double) (current_time - start_apple_time) / CLOCKS_PER_SEC;
        winner(g,snake1,current_time);
        //refresh();
        if(elapsed_time>0.5){
            ch = getch();//windows 自带函数，不会有输入显示
            //每0.5s，重新读取一次输入
            if(ch==ERR || if_backward(pre_input, ch)){ //如果没有检测到输入
                auto_snake_moving(g,snake1,pre_input,moving_time, board_start_time);
                //refresh();
            }
            else{
                step next_step_1 = get_next_step_no1(ch);
                start = ch;
                pre_direction = next_step_1;
                snake_moving(g, snake1, next_step_1);
                if (elapsed_time >= time_step) {// 更新蛇地图
                    clear();
                    pointboard(snake1,board_start_time);
                    move(6,0);
                    print(g);
                    //refresh();
                    move(0,0);
                }
            }
            bool if_exist_apple= find_apple(g);
            if (apple_generate_time <= elapsed_apple_time || !if_exist_apple) { //更新苹果地图
                point new_apple = random_generate_apple(g);
                while(new_apple.x== last_apple.x && new_apple.y== last_apple.y){
                    new_apple = random_generate_apple(g); // 如果和上个苹果一个位置就重新生成
                }
                g.a[new_apple.x][new_apple.y] = 'o';
                g.a[last_apple.x][last_apple.y] = ' '; //清扫原来的苹果位置
//                clear(); //和system("cls")一个效果，但似乎能避免和mvprintw冲突
//                pointboard(snake1,snake2,start_time);
//                move(6,0);
//                print(g);
//                refresh();
//                move(0,0);
                refresh();
                last_apple.x = new_apple.x;
                last_apple.y = new_apple.y;
                start_apple_time = current_time;
            }
        }
        move(0,0);
    }
    return 0;
}