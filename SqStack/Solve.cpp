#define _CRT_SECURE_NO_WARNINGS 1   //Mazeual Studio Scanf会被定义为不安全操作导致无法编译故将安全警告关闭
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include "SqStack.cpp"
#include"CreatPuzzle.cpp"
//□←→↓↑▓
//墙=0 走过=0;
int flag;
bool vis[SIZE][SIZE];
int b[][2] = { {0,0},{1, 0}, {0, 1}, {-1, 0}, {0, -1} };
struct Point
{
	int x, y, dir;
	Point(int a, int b, int c) 
	{
		x = a; y = b; dir = c;
	}
};
Point Next_Point(Point a)
{
	if (a.dir == 1) return Point(a.x + 1, a.y,1);
	if (a.dir == 2) return Point(a.x, a.y + 1, 1);
	if (a.dir == 3) return Point(a.x - 1, a.y, 1);
	if (a.dir == 4) return Point(a.x, a.y - 1, 1);
}
bool pass(int maze[][SIZE], Point pos) {
	return vis[pos.x][pos.y] && maze[pos.x][pos.y];
}
SqStack S=InitStack();
void dfs(int x, int y) {
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			vis[i][j] = true;
		}
	}
	//vis初始化
	Point Now(1,1,1);
	while (!StackEmpty(S)) 
	{
		if(pass(Maze,Now))
		{
			vis[Now.x][Now.y] = false;
			Point temp(Now.x, Now.y, 1);
			S = Push(S, temp);
		}
	}
}
void show() {

}
/*
void flsh() {
	for (int i = 0; i <= SIZE + 1; i++) {
		for (int j = 0; j <= SIZE + 1; j++) {
			if (!mp[i][j]) {
				if (!Maze[i][j])
					cout << "■";
				else if (Maze[i][j] == 1)
					cout << "↓";
				else if (Maze[i][j] == 2)
					cout << "→";
				else if (Maze[i][j] == 3)
					cout << "↑";
				else if (Maze[i][j] == 4)
					cout << "←";
				else if (Maze[i][j] == 6)
					cout << "O";
				else
					cout << "X";
			}
			else cout << "□";
		}
		cout << endl;
	}
}
*/