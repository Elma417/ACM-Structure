#define _CRT_SECURE_NO_WARNINGS 1   //Mazeual Studio Scanf会被定义为不安全操作导致无法编译故将安全警告关闭
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include "SqStack.cpp"
#include"CreatPuzzle.cpp"
int main()
{

	/*
	puts("请选择迷宫模式\n");
	puts("模式1为随机生成 模式2为文件输入");
	scanf("%d",&mode);
	if(mode==1)
	{
		Draw();

	}
	else
	{

	}
	*/
	Draw();
	for (int i = 0; i < SIZE; i++) {
		//printf("%d:\t", i);
		for (int j = 0; j < SIZE; j++)
			if (Maze[i][j] == 1) {
				printf("1");
			}
			else
			{
				printf("0");
			}
		printf("\n");
	}
	//show();
	return 0;
}