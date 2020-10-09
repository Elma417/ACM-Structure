#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<ctime>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
#define _CRT_SECURE_NO_WARNINGS 1   //Visual Studio Scanf会被定义为不安全操作导致无法编译故将安全警告关闭
#define INF 99999999
#define SIZE 11     //奇数，代表迷宫总大小
#define bug puts("ERROR\n")
using namespace std;
struct Node 
{
    int x, y;
    Node() { x = 0; y = 0; }
    Node(int x, int y,int dir) :x(x), y(y) {}
};
int Maze[SIZE][SIZE];
vector<Node>maze;//用于随机取点 
Node Move[4] = { Node(-1,0),Node(0,1),Node(1,0),Node(0,-1) };//上下左右移动 
int rand(int t) {//随机一个从0-(t-1)的整数 
    return (int)rand() % t;
}
void init() {//初始化 
    memset(Maze, 0, sizeof(Maze));
    srand(time(0));
    for (int i = 0; i < SIZE / 2; i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            maze.push_back(Node(i, j));
        }
    }
}
Node RandNode() {//返回一个列表中的随机节点 
    int temp = rand(maze.size());
    Node Now = maze[temp];
    return Now;
}
int FindWay(Node a) {//寻找可移动的方向 
    vector<int>temp;
    vector<int>reverse;
    for (int i = 0; i < 4; i++) {
        int tx = a.x + Move[i].x;
        int ty = a.y + Move[i].y;
        if (tx < 0 || tx >= SIZE / 2 || ty < 0 || ty >= SIZE / 2)continue;
        if (Maze[tx * 2 + 1][ty * 2 + 1] == 1) {
            reverse.push_back(i);
            continue;
        }
        temp.push_back(i);
    }
    if (temp.size() == 0) {
        //如果无可移动方向，则可能为死点，将其四周可联通的方向全打通 
        for (int i = 0; i < 4; i++) {
            int tempx = a.x * 2 + 1 + Move[i].x;
            int tempy = a.y * 2 + 1 + Move[i].y;
            if (tempx > 0 && tempx < SIZE - 1 && tempy>0 && tempy < SIZE - 1)
                Maze[tempx][tempy] = 1;
        }
        //如果是死点，则生成一个2*2的房间与周围相连,让它更像一个真正的迷宫
        for (int i = 0; i <= 1; i++) {
            for (int j = 0; j <= 1; j++) {
                int tx = a.x * 2 + 1 + i;
                int ty = a.y * 2 + 1 + j;
                if (tx > 0 && tx < SIZE - 1 && ty>0 && ty < SIZE - 1) {
                    Maze[tx][ty] = 1;
                }
            }
        }
        return -1;
    }
    else return temp[rand(temp.size())];
}
void Erase(Node t) {//删除节点，保证随机取点的正确性 
    int l = -1, r = maze.size();
    while (r - l > 1) {
        int temp = (l + r) / 2;
        if (maze[temp].x > t.x || (maze[temp].x == t.x && maze[temp].y > t.y)) {
            r = temp;
        }
        else l = temp;
    }
    Node lt = maze[l];
    maze.erase(maze.begin() + l);
}
void Creat() {//生成迷宫 
    while (maze.size()) {
        Node t = RandNode();
        queue<Node>q;
        q.push(t);
        int flag = 0;
        Maze[1][1] = 1;
        Maze[SIZE - 2][SIZE - 2] = 1;
        while (q.size()) {
            Node temp = q.front(); q.pop();
            Erase(temp);
            Maze[temp.x * 2 + 1][temp.y * 2 + 1] = 1;
            int Vocation = FindWay(temp);
            if (Vocation == -1)break;
            Node Direct = Move[Vocation];
            int Nx = temp.x * 2 + 1 + Direct.x, Ny = temp.y * 2 + 1 + Direct.y;
            Maze[Nx][Ny] = 1;
            q.push(Node(temp.x + Direct.x, temp.y + Direct.y));
        }
    }
}
void print() {//打印迷宫 
    for (int i = 0; i < SIZE; i++) {
        //printf("%d:\t", i);
        for (int j = 0; j < SIZE; j++)
            if (Maze[i][j] == 1) {
                printf("□");
            }
            else 
            {
                printf("■");
            }
        printf("\n");
    }
}
int Draw() {
    init();
    Creat();
    print();
    return 0;
}

