# snake


# 这是c++小组阶段性作业：贪吃蛇 的使用文档

我们组自选题目，贪吃蛇


***使用前言： 需安装PDcurses库，并在Clion上完成配置***

**使用说明：**
**具体见UI界面**，有详细的提示
如示例图：![输入图片说明](/imgs/2023-04-29/FiMqCBsi0rOnTPVh.png)
![输入图片说明](/imgs/2023-04-29/picjwL4c9X2Cx1YU.png)
![输入图片说明](/imgs/2023-04-29/jeY1rIPxyemetgxx.png)
![输入图片说明](/imgs/2023-04-29/o5AH3ljDQEiANhti.png)

**图中没有演示的功能还有**：
1. 简单和普通难度各一张，困难难度三张共5张地图可选择
2. 当“优雅”地（不临时变向而是在0.5s内自动运动）而吃到果子时，会在侧边栏浮现“excellent” "awesome"等字符（参考音乐游戏）
3. 最高分数的更新和记录
4. 程序的鲁棒性，能够处理不同的输入
5. 对开始结束的UI有多种设计，对应不同输入和结果
6. 连续按键加速蛇的运动！
7. 参考存活时间和蛇身长度的综合计分系统......


## 整体设计思路：

贪吃蛇整体包含4个部分，蛇在地图上运动的实现， 蛇吃的“果子”的生成和碰撞的检查，拓展的计分系统以及作为一个贪吃蛇游戏整体的UI设计






