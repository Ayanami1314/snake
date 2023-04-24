#include <iostream>
#include <ctime>
#include <random>
#include <curses.h> // 读取键盘上箭头的库
#include <deque> // 用来存储蛇身，不然没法更新蛇尾
#include <iomanip>
#include <unistd.h>

using namespace std;
// 这是一个贪吃蛇程序，需要注意的是，因为用到了非标准库（windows的conio.h）以处理键盘输入
// 在clion上运行需要一特殊操作(因为clion不支持conio.h)
// 1.将<conio.h> 替换为 <curses.h>。然后根据平台的不同，将 _getch() 函数替换为 getch() 函数（如之前的回答所述）。
//
// 2.在 CMakeLists.txt 文件中添加 curses 库。在文件中找到 target_link_libraries 一行，将其更改为如下内容：
//    target_link_libraries(${PROJECT_NAME} PRIVATE curses)
// 在visual studio 里面可以直接运行
int cur_time=60;
int next_step[4][2]={{-1,0},{1,0},{0,-1},{0,1}};//上下左右（wsad）
struct step{
    int x;
    int y;
};
struct graph{
    char a[101][101]; // 地图
    int x_width; // x宽
    int y_width; // y宽
};
struct point{
    int x;
    int y;
};
struct snake{
    int no;
    int len;
    point head;
    point tail;
    deque<point> body;
    char signal;
}snake1,snake2;
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
int score2(clock_t ctime){
    double rate = 0.1;//存活时间分数折算率
    return snake2.len+ rate*(60-cur_time);
}
void winner(graph& g,snake& s1,clock_t ctime,char special_control_signal=' '){
    //单个玩家的时候，如果时间清零，则输出分数
    //如果撞墙，则同二玩家
    if(cur_time<=0){
        system("cls");
        mvprintw(0,0,"Great! You win!");
        mvprintw(1,0,"You got score %d !",score1(60));
        refresh();
        system("pause"); //停住
    }
    else{
        if(snake_is_collision(g,s1,special_control_signal)){
            system("cls");
            mvprintw(0,0,"Game over!");
            mvprintw(1,0,"You collides with wall!");
            mvprintw(2,0,"You got score %d !  ... What a pity!",score2(60));
            refresh();
            system("pause");
        }
    }
}

void winner(graph& g,snake& s1,snake& s2,clock_t ctime,char special_control_signal=' '){ //重载，这是两玩家的时候
    if(cur_time<=0){
        system("cls");
        if(score1(ctime)>score2(ctime)) mvprintw(0,0,"Winner is the 1st player!");
        if(score1(ctime)<score2(ctime)) mvprintw(0,0,"Winner is the 2nd player!");
        if(score1(ctime)==score2(ctime)) mvprintw(0,0,"Draw!Why not play again?");
        system("pause"); //停住
    }
    else{
        if(snake_is_collision(g,s1,special_control_signal)){
            system("cls");
            mvprintw(0,0,"Game over!");
            mvprintw(1,0,"Player 1 collides with wall!");
            mvprintw(2,0,"Winner is the 2nd player!");
            refresh();
            system("pause");
        }
        if(snake_is_collision(g,s2)){
            system("cls");
            mvprintw(0,0,"Game over!");
            mvprintw(1,0,"Player 2 collides with wall!");
            mvprintw(2,0,"Winner is the 2nd player!");
            refresh();
            system("pause");
        }
    }
}
bool move_is_out_of_range(int x,int y,graph& g){
    // 判断坐标x,y 是否越界
    return  x<0 || x>g.x_width+1 || y<0 || y>g.y_width+1; //注意这里包括墙壁，为了处理碰撞的情况
}
bool is_out_of_range(int x,int y,graph& g){
    //move针对碰撞做了一些特化，正常的越界（苹果用）用这个
    return  x<1 || x>g.x_width || y<1 || y>g.y_width; //注意这里包括墙壁，为了处理碰撞的情况
}
void intitialize(graph& g,char boundary_signal='#'){
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
    for(i=0;i<g.x_width+2;i++){
        g.a[g.y_width][i]= boundary_signal;
    }
}
void intitialize2(graph& g,char boundary_signal='#'){
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
    for(i=5;i<=g.x_width-2;i++){
        g.a[5][i] = boundary_signal;
        g.a[g.y_width-2][i] = boundary_signal;
    }
    refresh();
}
void intitialize3(graph& g,char boundary_signal='#'){
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
    for(i=5;i<=9;i++){
        g.a[5][i]=boundary_signal;
        g.a[5][g.x_width-11+i]=boundary_signal;
        g.a[g.y_width-2][i]=boundary_signal;
        g.a[g.y_width-2][g.x_width-11+i]=boundary_signal;
    }
    for(j=1;j<=4;j++){
        g.a[5+j][5]=boundary_signal;
        g.a[5+j][g.x_width-2]=boundary_signal;
        g.a[g.y_width-2-j][5]=boundary_signal;
        g.a[g.y_width-2-j][g.x_width-2]=boundary_signal;
    }
    refresh();
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
        mvprintw(row+i,col,g.a[i]);
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

bool isapple(graph& g,int x,int y,char apple_signal='o'){// apple_signal 按后续函数实现改
    return g.a[x][y]==apple_signal;
}
void snake_moving(graph& g,snake& s, step next,char boudary_signal='#'){
    int next_x = s.head.x+next.x;
    int next_y = s.head.y+next.y;
    // 更新蛇头的坐标
    if(move_is_out_of_range(next_x,next_y,g)){
        winner(g,s,(60-cur_time)*CLOCKS_PER_SEC,'?');
        return;
    }
    if(g.a[next_x][next_y]==boudary_signal){
        winner(g,s,(60-cur_time)*CLOCKS_PER_SEC,'?');
        return;
    }
    if(s.no==1){
        snake1.head.x = next_x;
        snake1.head.y = next_y;
        snake1.body.push_back(snake1.head);
    }
    if(s.no==2){
        snake2.head.x = next_x;
        snake2.head.y = next_y;
        snake2.body.push_back(snake2.head);
    }
    // 更新地图

    // 更新蛇尾
    if(!isapple(g,next_x,next_y)){
        //清除尾部
        g.a[s.tail.x][s.tail.y] = ' ';
        if(s.no == 1){
            snake1.body.pop_front();//删除原来的蛇尾
            snake1.tail = snake1.body[0];//蛇尾的起始位置
        }
        if(s.no == 2){
            snake2.body.pop_front();//删除原来的蛇尾
            snake2.tail = snake2.body[0];//蛇尾的起始位置
        }
    }
    else{
        //蛇伸长1
        g.a[s.tail.x][s.tail.y] = s.signal;
        if(s.no==1) snake1.len++;
        if(s.no==2) snake2.len++;
    }
    g.a[next_x][next_y]=s.signal;// 先判断再更新地图
}
bool apple_pos_is_legal(int x, int y, graph& g){
    // 判断生成苹果坐标是否合法,合法：不越界、不在蛇身上
    return !is_out_of_range(x,y,g) && g.a[x][y]!=snake1.signal && g.a[x][y]!=snake2.signal && g.a[x][y]!='#';
}
point random_generate_apple(graph& g,char apple_signal='o',char signal_1='*',char signal_2='+'){
    srand(time(NULL)); //随机数种子
    int x = rand()%g.x_width+1; //产生一个1到x_width的随机整数
    int y = rand()%g.y_width+1; //产生一个1到y_width的随机整数
    while(!apple_pos_is_legal(x,y,g)){ //如果坐标不合法，重新生成坐标)
        g.a[x][y]=apple_signal;
    }
    point apple = {x,y};
    return apple;
}

//void inline winner(){
//    ;
//}
const char* int_to_string(int a){
    string s="";
    while(a>0){
        s+=a%10+'0';
        a/=10;
    }
    string rev_s="";
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
    mvprintw(4,0,"Score:%d",score2(ctime));
    mvprintw(5,0,"-----------------Snake------------------------");
    refresh();
    move(6,0);
}
void auto_snake_moving(graph&g,snake&s,char ch_for_direction,clock_t& start_time,clock_t& board_start_time,int player_no=1,double delta_t = 0.5){
    // 贪吃蛇需要有自动移动的部分
    // delta_t：移动一格动作时间间隔，单位s
    // 自动移动部分应在移动完成后自动执行

    clock_t now = clock();
    step auto_next;
    switch(player_no){
        case 1:auto_next = get_next_step_no1(ch_for_direction);break;
        case 2:auto_next = get_next_step_no2(ch_for_direction);break;
        default: return;
    }

    if(double(now - start_time)/CLOCKS_PER_SEC >= delta_t){ // 别忘记除CLOCKS_PER_SEC
        snake_moving(g,s,auto_next);
        clear();
        pointboard(snake1,snake2,board_start_time);
        refresh();
        move(6,0);
        print(g);
        refresh();
        move(0,0);
        start_time = now;
    }
}
enum mode{
    easy,
    medium,
    hard
};

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
int main() {
    initscr(); // 初始化PDCurses库

    int x_width = 20;
    int y_width = 20;
    double time_step = 1.0/60.0; // 60fps
    mode player_mode; //难度
    graph g;
    g.x_width = x_width;
    g.y_width = y_width;
    int i, j;
    for (i = 0; i < x_width + 2; i++) {
        for (j = 0; j < y_width + 2; j++) {
            g.a[i][j] = ' ';
        }
    }

    mvprintw(0,0,"Please choose a mode(1:easy, 2:medium, 3:hard)"); //窗口打印
    move(1,0);//将光标移动到第二行第一列

    int player_mode_num;
    bool valid_input = false;
    while (!valid_input) {
        player_mode_num = getch();
        switch(player_mode_num){
            case '1':
                player_mode = easy;
                valid_input = true;
                intitialize(g);
                break;
            case '2':
                player_mode = medium;
                valid_input = true;
                intitialize2(g);
                break;
            case '3':
                player_mode = hard;
                valid_input = true;
                intitialize3(g);
                break;
            default:
                refresh(); // 刷新窗口
                mvprintw(0, 0, "Illegal input! Please choose mode again......");
                mvprintw(1,0,"Please choose a mode(1:easy, 2:medium, 3:hard)"); //窗口打印
        }
    }
    snake_begin(g, 1, 10, 10);
    snake_begin(g, 2, 15, 15);
    int apple_generate_time= apple_generate(player_mode);
    mvprintw(3, 0, "Great! Let's begin the game!");
    refresh();

    //sleep(3);
    clear();
    mvprintw(0,1,"Press 'W' or 'A' or 'S' or 'D' to start...");
    refresh();
    char start = getch();
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
//    move(0,0);
    while (1) {
        clock_t current_time = clock();
        double elapsed_time = (double) (current_time - start_time) / CLOCKS_PER_SEC;
        double elapsed_apple_time = (double) (current_time - start_apple_time) / CLOCKS_PER_SEC;
        winner(g,snake1,current_time);
        if(elapsed_time>0.5){
            char ch = getch();//windows 自带函数，不会有输入显示
            //每0.5s，重新读取一次输入
            if(ch==ERR){ //如果没有检测到输入
                auto_snake_moving(g,snake1,start,moving_time, board_start_time);
            }
            else{
                step next_step_1 = get_next_step_no1(ch);
                start = ch;
                pre_direction = next_step_1;
                snake_moving(g, snake1, next_step_1);
                if (elapsed_time >= time_step) {// 更新蛇地图
                    clear();
                    pointboard(snake1,snake2,board_start_time);
                    move(6,0);
                    print(g);
                    refresh();
                    move(0,0);
                }
                //input_constraint();
            }
            if (apple_generate_time <= elapsed_apple_time) { //更新苹果地图
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
                last_apple.x = new_apple.x;
                last_apple.y = new_apple.y;
                start_apple_time = current_time;
            }
        }
        move(0,0);
    }
    return 0;
}