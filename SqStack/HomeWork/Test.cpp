#define _CRT_SECURE_NO_WARNINGS 1   //Visual Studio Scanf会被定义为不安全操作导致无法编译故将安全警告关闭
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include"Solve.cpp"

//控制用户界面的交互
int main()
{
	int choice[4];
	for (int i = 1; i <= 4; i++)
		dirr[i] = i;
	dirr[5] = 1;
	SqStack S;
	InitStack(&S);
	PosType start, end;
	while (1)
	{
		fflush(stdin);
		system("cls");
		puts("---------------Main Memu---------------");
	//		puts("                       游戏目录");
		puts("------------1.设定迷宫大小------------");
		puts("------------2.自动生成迷宫------------");
		puts("------------3.文件导入迷宫------------");
		puts("------------4.修改遍历顺序------------");
		puts("------------5.动态显示路径------------");
		puts("------------6.输出所有路径------------");
		puts("------------7.输出最短路径------------");
		puts("------------8.退出迷宫程序------------");
		puts("---------------------------------------");
		printf("请输入您的选择:");
		int opt;
		if (!scanf("%d", &opt) || opt < 1 || opt > 8) //检查输入
		{
			fflush(stdin);
			puts("输入非法，请重新输入！");
			Sleep(1600);
			continue;
		}
		fflush(stdin);
		switch (opt)
		{

		case 8: //8.退出迷宫程序
		{
			system("cls");
			puts("程序已退出！\n感谢您的使用！\n");
			puts("班级：19184115");
			puts("专业:计算机科学与技术（人工智能与大数据）创新实验班");
			puts("姓名：周建屹");

			system("PAUSE");
			return 0;
		}
		case 1: //1.设定迷宫大小
		{
			memset(choice, 0, sizeof(choice));
			choice[1] = 1;
			while (1)
			{
				system("cls");
				puts("请输入迷宫的宽(5~10)：");
				if (scanf("%d", &M) == 0 || M > 10 || M < 5)
				{
					fflush(stdin);
					puts("输入非法，请重新输入！");
					Sleep(1600);
					continue;
				}
				break;
			}
			while (1)
			{
				system("cls");
				puts("请输入迷宫的长(5~10)：");
				scanf("%d", &N);
				if (N > 10 || N < 5)
				{
					fflush(stdin);
					puts("输入非法，请重新输入！");
					Sleep(1600);
					continue;
				}
				break;
			}
			puts("迷宫设置完毕！\n请按回车返回主菜单");
			start.x = 1;
			start.y = 0;
			end.x = M - 2;
			end.y = N - 1;
			fflush(stdin);
			system("PAUSE");
			break;
		}
		case 2: //2.自动生成迷宫
		{
			system("cls");
			if (choice[1] == 0)
			{
				puts("请先设定迷宫大小！");
				Sleep(1600);
				continue;
			}
			choice[2] = 1;
			choice[3] = 0;
			do
			{
				Random();
				DynamicDFS(start, end, &S, 0);
			} while (count == 0); //随机生成迷宫直到迷宫可通
			memset(vis, 0, sizeof(vis));
			puts("迷宫生成成功！");
			puts("随机生成的迷宫为：");
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < N; j++)
					if (Maze[i][j] == 1)
						printf("■");
					else
						printf("□");
				puts("");
			}
			count = 0;
			puts("\n请按回车返回主菜单\n");
			system("PAUSE");
				break;
		}
		case 3: //3.文件导入迷宫
		{
			system("cls");
			if (choice[1] == 0)
			{
				puts("请先设定迷宫大小！");
				system("PAUSE");
					continue;
			}
			choice[2] = 0;
			choice[3] = 1;
			FILE* fp;
			if ((fp = fopen("input.txt", "r")) == NULL)
			{

				system("cls");
				printf("输入文件不存在!\n");
				puts("\n程序已退出，感谢您的使用！\n");
				system("PAUSE");
					return 0;
			}
			for (int i = 0; i <= M - 1; i++)
				for (int j = 0; j <= N - 1; j++)
				{
					Maze[i][j] = -1;
					if (fscanf(fp, "%d", &Maze[i][j]) == EOF || (Maze[i][j] != 0 && Maze[i][j] != 1))
					{
						system("cls");
						printf("输入文件不合法!\n");
						puts("\n程序已退出，感谢您的使用！\n");
						system("PAUSE");
							return 0;
					}
				}
			int test = -19195216;
			fscanf(fp, "%d", &test);
			if (test != -19195216)
			{
				system("cls");
				printf("输入文件不合法!\n");
				puts("\n程序已退出，感谢您的使用！\n");
				system("PAUSE");
					return 0;
			}
			puts("迷宫读取成功！");
			puts("输入文件中的迷宫为：");
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < N; j++)
					if (Maze[i][j] == 1)
						printf("■");
					else
						printf("□");
				puts("");
			}
			DynamicDFS(start, end, &S, 0);
			if (count == 0)
			{
				system("cls");
				printf("该迷宫无解!\n");
				puts("\n程序已退出，感谢您的使用！\n");
				system("PAUSE");
					return 0;
			}
			memset(vis, 0, sizeof(vis));
			puts("");
			count = 0;
			fclose(fp);
			puts("\n请按回车返回主菜单\n");
			system("PAUSE");
				break;
		}
		case 4: //4.修改遍历顺序
		{
			system("cls");
			while (1)
			{
				system("cls");
				puts("请输入遍历顺序对应的编号：1.右 2.下 3.左 4.上");
				puts("请输入第一个：");
				scanf("%d", &dirr[1]);
				if (dirr[1] != 1 && dirr[1] != 2 && dirr[1] != 3 && dirr[1] != 4)
				{
					fflush(stdin);
					puts("输入非法！请再次输入！\n");
					Sleep(1600);
					continue;
				}

				puts("请输入第二个：");
				scanf("%d", &dirr[2]);
				if ((dirr[2] != 1 && dirr[2] != 2 && dirr[2] != 3 && dirr[2] != 4) || dirr[2] == dirr[1])
				{
					fflush(stdin);
					puts("输入非法！请再次输入！\n");
					Sleep(1600);
					continue;
				}

				puts("请输入第三个：");
				scanf("%d", &dirr[3]);
				if ((dirr[3] != 1 && dirr[3] != 2 && dirr[3] != 3 && dirr[3] != 4) || dirr[3] == dirr[2] || dirr[3] == dirr[1])
				{
					fflush(stdin);
					puts("输入非法！请再次输入！\n");
					Sleep(1600);
					continue;
				}

				puts("请输入第四个：");
				scanf("%d", &dirr[4]);
				if ((dirr[4] != 1 && dirr[4] != 2 && dirr[4] != 3 && dirr[4] != 4) || dirr[4] == dirr[3] || dirr[4] == dirr[2] || dirr[4] == dirr[1])
				{
					fflush(stdin);
					puts("输入非法！请再次输入！\n");
					Sleep(1600);
					continue;
				}

				break;
			}
			puts("遍历顺序修改成功！");
			puts("\n请按回车返回主菜单\n");
			system("PAUSE");
				break;
		}
		case 5: //5.动态显示路径
		{
			system("cls");
			if (choice[1] == 0)
			{
				puts("请先设定迷宫大小！");
				Sleep(1600);
				continue;
			}
			if (choice[2] + choice[3] == 0)
			{
				puts("请先 随机生成 或 读取迷宫！");
				Sleep(1600);
				continue;
			}
			DynamicDFS(start, end, &S, 1);
			count = 0;
			StackClear(&S);
			memset(vis, 0, sizeof(vis));
			puts("动态显示完毕！");
			puts("\n请按回车返回主菜单\n");
			system("PAUSE");
				break;
		}
		case 6: //6.输出所有路径
		{
			system("cls");
			if (choice[1] == 0)
			{
				puts("请先设定迷宫大小！");
				Sleep(1600);
				continue;
			}
			if (choice[2] + choice[3] == 0)
			{
				puts("请先 随机生成 或 读取迷宫！");
				Sleep(1600);
				continue;
			}
			puts("随机生成的迷宫为：");
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < N; j++)
					if (Maze[i][j] == 1)
						printf("■");
					else
						printf("□");
				puts("");
			}
			puts("\n");
			MultipleDfs(start, end, &S);
			if (count == 10)
				puts("\n已显示10条路径，剩余路径省略！\n");
			count = 0;
			StackClear(&S);
			memset(vis, 0, sizeof(vis));
			puts("\n请按回车返回主菜单\n");
			system("PAUSE");
				break;
		}
		case 7: //7.输出最短路径
		{
			system("cls");
			if (choice[1] == 0)
			{
				puts("请先设定迷宫大小！");
				Sleep(1600);
				continue;
			}
			if (choice[2] + choice[3] == 0)
			{
				puts("请先 随机生成 或 读取迷宫！");
				Sleep(1600);
				continue;
			}
			OptimalDfs(start, end, &S, 1);
			if (count < 10)
				printf("一共有%d条最短路；最短的路径长度为%d。\n", count, minlength);
			else
				puts("\n已显示10条最短路，剩余路径省略！\n");
			count = 0;
			StackClear(&S);
			memset(vis, 0, sizeof(vis));
			puts("\n请按回车返回主菜单\n");
			system("PAUSE");
				break;
		}
		}
	}
}