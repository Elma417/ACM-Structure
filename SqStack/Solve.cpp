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
Status Judge(PosType e)				//判断是否可走
{
	if (e.x >= 0 && e.x < M && e.y >= 0 && e.y < N && Maze[e.x][e.y] == 0) return OK;
	return OVERFLOW;
}
PosType NextPos(PosType e, int dir)  //下一步
{
	PosType E;
	switch (dir)
	{
	case 1:E.x = e.x; E.y = e.y + 1; break;//向下
	case 2:E.x = e.x + 1; E.y = e.y; break;//向右	
	case 3:E.x = e.x; E.y = e.y - 1; break;//向上
	default:E.x = e.x - 1; E.y = e.y;	   //向左   
	}
	return E;
}
void PrintPath(SqStack* s)
{
	int isFirst = TRUE;
	SqStack TempStack;
	InitStack(&TempStack);
	SElemType TempValue;
	while (!StackEmpty((*s)))
	{
		Pop(s, &TempValue);
		Push(&TempStack, TempValue);
	}
	while (!StackEmpty((TempStack)))
	{
		Pop(&TempStack, &TempValue);
		Push(s, TempValue);
		if (isFirst) isFirst = FALSE;
		else printf("->");
		printf("(%d,%d)", TempValue.seat.x, TempValue.seat.y);
	}
	puts("\n");
}
void PrintMaze()					//打印迷宫
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Maze[i][j] == 0 && vis[i][j] > 0)
			{
				switch (vis[i][j])
				{
				case 1:printf("→"); break;
				case 2:printf("↓"); break;
				case 3:printf("←"); break;
				default:printf("↑");
				}
			}
			else if (Maze[i][j] == 1) printf("■");						//迷宫的墙
			else if (Maze[i][j] == 0 && vis[i][j] == -1) printf("×");      //不通的路
			else printf("□");										//迷宫未走的路
		}
		puts("");
	}
}
Status DynamicMazePath(PosType start, PosType end, SqStack* s)//动态显示路径
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
			if (!StackEmpty(*s))
			{
				Pop(s, &e);
				while (e.di == 4 && !StackEmpty(*s))
					//四个方向均探索后说明该位置无法通过，为死角 
				{
					vis[e.seat.x][e.seat.y] = -1;
					Pop(s, &e);
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
	} while (!StackEmpty(*s));
	return FALSE;
}
void dfs(PosType start, PosType end, SqStack* s)				//深度搜索所有路径
{
	if (count >= 100) return;
	if (start.x == end.x && start.y == end.y)
	{
		PrintMaze();
		printf("第%d条路径已找到！\n", ++count);
		PrintPath(s);
		puts("");
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
		Pop(s, &nextpos);
	}
}
void dfs2(PosType start, PosType end, SqStack* s, int len)		//深度搜索最短路径
{
	if (start.x == end.x && start.y == end.y)
	{
		if (len == minlength)
		{
			PrintMaze();
			printf("第%d条路径已找到！\n", ++count);
			PrintPath(s);
			puts("");
			return;
		}
		else if (len < minlength)
		{
			minlength = len;
			system("cls");
			puts("随机生成的地图为：");
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < N; j++)
					if (Maze[i][j] == 1) printf("■");
					else printf("□");
				puts("");
			}
			puts("\n");
			count = 1;
			PrintMaze();
			printf("第%d条路径已找到！\n", count);
			PrintPath(s);
			puts("");
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
		Pop(s, &nextpos);
	}
}