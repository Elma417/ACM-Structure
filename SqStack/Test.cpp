#define _CRT_SECURE_NO_WARNINGS 1   //Mazeual Studio Scanf�ᱻ����Ϊ����ȫ���������޷�����ʽ���ȫ����ر�
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include "SqStack.cpp"
#include"CreatPuzzle.cpp"
int main()
{

	/*
	puts("��ѡ���Թ�ģʽ\n");
	puts("ģʽ1Ϊ������� ģʽ2Ϊ�ļ�����");
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