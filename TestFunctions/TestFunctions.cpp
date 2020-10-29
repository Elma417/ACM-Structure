#define _CRT_SECURE_NO_WARNINGS 1   //Visual Studio Scanf会被定义为不安全操作导致无法编译故将安全警告关闭
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
int main()
{
	int Maze[100][100];
	int M = 0;
	int N = 1;
	double tmp = 0;	//当前读入的数值
	system("cls");
	FILE* fp;
	
	if ((fp = fopen("input.txt", "r")) == NULL)
	{
		system("cls");
		printf("File Not Exist!!\n");
		puts("\nProgram has exited！\n");
		system("PAUSE");
		return 0;
	}//判空
	/*
		for (int i = 0; i <= M - 1; i++)
		for (int j = 0; j <= N - 1; j++)
		{
			Maze[i][j] = -1;
			if (fscanf(fp, "%d", &Maze[i][j]) == EOF || (Maze[i][j] != 0 && Maze[i][j] != 1))
			{
				system("cls");
				printf("Invalid input file!\n");
				puts("\nProgram has exited！\n");
				system("PAUSE");
				return 0;
			}
		}
	int test = -114;
	fscanf(fp, "%d", &test);
	if (test != -114)
	{
		system("cls");
		printf("Invalid input file!\n");
		puts("\nProgram has exited！\n");
		system("PAUSE");
		return 0;
	}
	puts("The maze is successfully read！");
	puts("The maze in the input file is：");
	*/
	char c;
	int temp;
	fscanf(fp, "%c", &c);
	while (('\n' != c)) 
	{
		fscanf(fp, "%c", &c);
		 if(c == '0'|| c =='1')N++;
	}
	fp = fopen("input.txt", "r");
	while (fscanf(fp, "%d", &temp) != EOF) {
		for (int i = 0;i < N;i++)
		{
			fscanf(fp, "%d", &temp);
		}
		M++;
	}
	printf("%d\n",N);
	printf("%d", M);

	fclose(fp);
	/*
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			if (Maze[i][j] == 1)
				printf("■");
			else
				printf("□");
		puts("");
	}
	*/
}
