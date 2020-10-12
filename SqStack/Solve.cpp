#define _CRT_SECURE_NO_WARNINGS 1   //Mazeual Studio Scanf�ᱻ����Ϊ����ȫ���������޷�����ʽ���ȫ����ر�
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<time.h>
#include <windows.h>
#include "SqStack.cpp"
#include"CreatPuzzle.cpp"
//������������
//ǽ=0 �߹�=0;
typedef int Status;
Status DynamicMazePath(int maze, PosType start, PosType end, SqStack& s)
{
	PosType curpos;
	InitStack(s);
	SElemType e;
	int curstep;
	curpos = start;	// �趨"��ǰλ��"Ϊ"���λ��"
	curstep = 1;		// ̽����һ��
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
		{	//��ǰλ�ÿ�ͨ��������δ���ߵ�����ͨ����
			vis[curpos.x][curpos.y] = 1;
			e.di = 1;
			e.ord = curstep;
			e.seat = curpos;
			Push(s, e);	// ����·��
			if (curpos.x == end.x && curpos.y == end.y)
			{
				vis[M - 2][N - 1] = 1;
				Sleep(100);
				system("cls");
				PrintMaze();
				return TRUE;
			}
			curpos = NextPos(curpos, 1);	// ��һλ���ǵ�ǰλ�õ��Ҳ�
			curstep++;	 //̽����һ��
		}
		else
		{	//��ǰλ�ò���ͨ��
			if (!StackEmpty(s))
			{
				Pop(s, e);
				while (e.di == 4 && !StackEmpty(s))
					//�ĸ������̽����˵����λ���޷�ͨ����Ϊ���� 
				{
					vis[e.seat.x][e.seat.y] = -1;
					Pop(s, e);
				}
				if (e.di < 4)
				{
					e.di++;
					vis[e.seat.x][e.seat.y]++;
					Push(s, e);						//���²���ͨ���ı�ǣ����˻�һ��
					curpos = NextPos(e.seat, e.di);	// ��ǰλ����Ϊ�·�������ڿ�
				}
			}
		}
		Sleep(100);  	//��ʱ 
		system("cls");  //���� 
	} while (!StackEmpty(s));
	return FALSE;
}
void dfs(PosType start, PosType end, SqStack& s)
{
	if (start.x == end.x && start.y == end.y)
	{
		printf("��%d��·�����ҵ���\n", ++count);
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
					cout << "��";
				else if (Maze[i][j] == 1)
					cout << "��";
				else if (Maze[i][j] == 2)
					cout << "��";
				else if (Maze[i][j] == 3)
					cout << "��";
				else if (Maze[i][j] == 4)
					cout << "��";
				else if (Maze[i][j] == 6)
					cout << "O";
				else
					cout << "X";
			}
			else cout << "��";
		}
		cout << endl;
	}
}
*/