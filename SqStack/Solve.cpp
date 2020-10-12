#define _CRT_SECURE_NO_WARNINGS 1   //Mazeual Studio Scanf会被定义为不安全操作导致无法编译故将安全警告关闭
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<time.h>
#include <windows.h>
#include "SqStack.cpp"
#include"CreatPuzzle.cpp"
//□←→↓↑▓
//墙=0 走过=0;
typedef int Status;
Status DynamicMazePath(int maze, PosType start, PosType end, SqStack& s)
{
	PosType curpos;
	InitStack(s);
	SElemType e;
	int curstep;
	curpos = start;	// 设定"当前位置"为"入口位置"
	curstep = 1;		// 探索第一步
	do
	{
		if (vis[1][1] == -1)
		{
			vis[1][0] = -1;
			Sleep(500);
			system("cls");
			PrintMaze();
			return FALSE;
		}
		PrintMaze();
		if (!vis[curpos.x][curpos.y] && Judge(curpos))
		{	//当前位置可通过，即是未曾走到过的通道块
			vis[curpos.x][curpos.y] = 1;
			e.di = 1;
			e.ord = curstep;
			e.seat = curpos;
			Push(s, e);	// 加入路径
			if (curpos.x == end.x && curpos.y == end.y)
			{
				vis[M - 2][N - 1] = 1;
				Sleep(100);
				system("cls");
				PrintMaze();
				return TRUE;
			}
			curpos = NextPos(curpos, 1);	// 下一位置是当前位置的右侧
			curstep++;	 //探索下一步
		}
		else
		{	//当前位置不能通过
			if (!StackEmpty(s))
			{
				Pop(s, e);
				while (e.di == 4 && !StackEmpty(s))
					//四个方向均探索后说明该位置无法通过，为死角 
				{
					vis[e.seat.x][e.seat.y] = -1;
					Pop(s, e);
				}
				if (e.di < 4)
				{
					e.di++;
					vis[e.seat.x][e.seat.y]++;
					Push(s, e);						//留下不能通过的标记，并退回一步
					curpos = NextPos(e.seat, e.di);	// 当前位置设为新方向的相邻块
				}
			}
		}
		Sleep(100);  	//延时 
		system("cls");  //清屏 
	} while (!StackEmpty(s));
	return FALSE;
}
void dfs(PosType start, PosType end, SqStack& s)
{
	if (start.x == end.x && start.y == end.y)
	{
		printf("第%d条路径已找到！\n", ++count);
		PrintMaze();
		return;
	}
	for (int i = 1; i <= 4; i++)
	{
		SElemType nextpos;
		nextpos.seat = NextPos(start, i);
		if (vis[nextpos.seat.x][nextpos.seat.y] || !Judge(nextpos.seat)) continue;
		vis[start.x][start.y] = i;
		vis[nextpos.seat.x][nextpos.seat.y] = 1;
		Push(s, nextpos);
		dfs(nextpos.seat, end, s);
		vis[nextpos.seat.x][nextpos.seat.y] = 0;
		Pop(s, nextpos);
	}
}
void dfs2(PosType start, PosType end, SqStack& s, int len)
{
	if (start.x == end.x && start.y == end.y)
	{
		if (len == minlength) PrintMaze(), count++;
		else if (len < minlength)
		{
			minlength = len;
			system("cls");
			count = 1;
			PrintMaze();
		}
		return;
	}
	for (int i = 1; i <= 4; i++)
	{
		SElemType nextpos;
		nextpos.seat = NextPos(start, i);
		if (vis[nextpos.seat.x][nextpos.seat.y] || !Judge(nextpos.seat)) continue;
		vis[start.x][start.y] = i;
		vis[nextpos.seat.x][nextpos.seat.y] = 1;
		Push(s, nextpos);
		dfs2(nextpos.seat, end, s, len + 1);
		vis[nextpos.seat.x][nextpos.seat.y] = 0;
		Pop(s, nextpos);
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