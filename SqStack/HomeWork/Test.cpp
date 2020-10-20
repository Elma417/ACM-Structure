#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "SqStack.cpp"
int M;	   //迷宫的宽
int N;	   //迷宫的长
int P = 8; //随机生成迷宫的路和墙的期望比值(P:10-P)
int Maze[20][20], vis[20][20];
int count = 0;			 //路径总数
int dirr[6];			 //遍历顺序
int minlength = 20 * 20; //目前最小的路径长度
int opt, opt1, opt2;
void Random() //随机生成迷宫的函数
{
	srand(time(NULL));
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i <= M - 1; i++) //按照所给比例生成墙
		for (int j = 0; j <= N - 1; j++)
			if ((rand() % 10 >= P) || i == 0 || j == 0 || i == M - 1 || j == N - 1)
				Maze[i][j] = 1;
			else
				Maze[i][j] = 0;

	for (int i = 1; i <= M - 2; i++) //如果一条路四周都是墙，那么全部打通
		for (int j = 1; j <= N - 2; j++)
			if (Maze[i][j] == 0 && Maze[i + 1][j] == 1 && Maze[i - 1][j] == 1 && Maze[i][j + 1] == 1 && Maze[i][j - 1] == 1)
				Maze[i + 1][j] = Maze[i - 1][j] = Maze[i][j + 1] = Maze[i][j - 1] = 0;

	Maze[1][0] = Maze[1][1] = Maze[M - 2][N - 1] = Maze[M - 2][N - 2] = 0;
	//起点右终点左打通
	for (int i = 1; i <= M - 2; i++) //如果一条路四周都是路，把这条路堵死，防止路径过多
		for (int j = 1; j <= N - 2; j++)
			if (Maze[i][j] == 0 && Maze[i + 1][j] == 0 && Maze[i - 1][j] == 0 && Maze[i][j + 1] == 0 && Maze[i][j - 1] == 0 && Maze[i + 1][j + 1] == 0 && Maze[i - 1][j - 1] == 0 && Maze[i + 1][j - 1] == 0 && Maze[i - 1][j + 1] == 0)
				Maze[i][j] = 1;
}
Status Judge(PosType e) //判断是否可走
{
	if (e.x >= 0 && e.x < M && e.y >= 0 && e.y < N && Maze[e.x][e.y] == 0 && vis[e.x][e.y] == 0)
		return OK;
	return OVERFLOW;
}
PosType NextPos(PosType e, int dir) //下一步
{
	PosType E;
	switch (dirr[dir])
	{
	case 1:
		E.x = e.x;
		E.y = e.y + 1;
		break; //向右
	case 2:
		E.x = e.x + 1;
		E.y = e.y;
		break; //向下
	case 3:
		E.x = e.x;
		E.y = e.y - 1;
		break; //向左
	default:
		E.x = e.x - 1;
		E.y = e.y; //向上
	}
	return E;
}
void PrintPath(SqStack* s) //打印路径
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
		if (isFirst)
			isFirst = FALSE;
		else
			printf("->");
		printf("(%d,%d)", TempValue.seat.x, TempValue.seat.y);
	}
	puts("\n");
}
void PrintMaze() //打印迷宫
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Maze[i][j] == 0 && vis[i][j] > 0)
			{
				switch (dirr[vis[i][j]])
				{
				case 1:
					printf("→");
					break;
				case 2:
					printf("↓");
					break;
				case 3:
					printf("←");
					break;
				case 4:
					printf("↑");
				}
			}
			else if (vis[i][j] == -1)
				printf("×"); //不通的路
			else if (Maze[i][j] == 1)
				printf("■"); //迷宫的墙
			else
				printf("□"); //迷宫未走的路
		}
		puts("");
	}
}
void DFS(PosType start, PosType end, SqStack* s, int sta)
//sta=0时,检测是否可通；sta=1时，深度搜索路径
{
	if (count == 1)
		return;
	if (start.x == end.x && start.y == end.y)
	{
		vis[end.x][end.y] = 5;
		count = 1;
		if (sta == 1)
		{
			Sleep(100);
			system("cls");
			PrintMaze();
			puts("找到路径:");
			PrintPath(s);
			puts("");
		}
		return;
	}
	for (int i = 1; i <= 4; i++)
	{
		if (count == 1)
			return;
		SElemType nextpos;
		nextpos.seat = NextPos(start, i);
		vis[start.x][start.y] = i;
		if (sta == 1)
		{
			Sleep(100);
			system("cls");
			PrintMaze();
		}
		if (!Judge(nextpos.seat))
		{
			if (i == 4)
			{
				vis[start.x][start.y] = -1;
				if (sta == 1)
				{
					Sleep(100);
					system("cls");
					PrintMaze();
				}
				return;
			}
			continue;
		}
		vis[nextpos.seat.x][nextpos.seat.y] = 1;
		Push(s, nextpos);
		DFS(nextpos.seat, end, s, sta);
		if (vis[nextpos.seat.x][nextpos.seat.y] != -1)
			vis[nextpos.seat.x][nextpos.seat.y] = 0;
		Pop(s, &nextpos);
	}
}
void MulDfs(PosType start, PosType end, SqStack* s) //深度搜索所有路径
{
	if (count >= 10)
		return;
	if (start.x == end.x && start.y == end.y)
	{
		vis[end.x][end.y] = 5;
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
		if (!Judge(nextpos.seat))
			continue;
		vis[start.x][start.y] = i;
		vis[nextpos.seat.x][nextpos.seat.y] = 1;
		Push(s, nextpos);
		MulDfs(nextpos.seat, end, s);
		vis[nextpos.seat.x][nextpos.seat.y] = 0;
		Pop(s, &nextpos);
	}
}
void BestDfs(PosType start, PosType end, SqStack* s, int len) //深度搜索最短路径
{
	if (start.x == end.x && start.y == end.y)
	{
		if (len == minlength)
		{
			vis[end.x][end.y] = 5;
			count++;
			if (count <= 10)
			{
				PrintMaze();
				printf("第%d条路径已找到！\n", count);
				PrintPath(s);
				puts("");
			}
			return;
		}
		else if (len < minlength)
		{
			minlength = len;
			system("cls");
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
		if (!Judge(nextpos.seat))
			continue;
		vis[start.x][start.y] = i;
		vis[nextpos.seat.x][nextpos.seat.y] = 1;
		Push(s, nextpos);
		BestDfs(nextpos.seat, end, s, len + 1);
		vis[nextpos.seat.x][nextpos.seat.y] = 0;
		Pop(s, &nextpos);
	}
}
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
		puts("*************************Maze*************************");
		puts("*********************洪智豪&周建屹*********************");
		puts("                       游戏目录");
		puts("                   1.设定迷宫大小");
		puts("                   2.自动生成迷宫");
		puts("                   3.文件导入迷宫");
		puts("                   4.修改遍历顺序");
		puts("                   5.动态显示路径");
		puts("                   6.输出所有路径");
		puts("                   7.输出最短路径");
		puts("                   8.退出迷宫程序");
		puts("******************************************************");
		printf("请输入您的选择:");
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
			puts("代码:洪智豪 19195216         文档:周建屹 19151135");

			if (getchar())
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
			if (getchar())
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
				DFS(start, end, &S, 0);
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
			if (getchar())
				break;
		}
		case 3: //3.文件导入迷宫
		{
			system("cls");
			if (choice[1] == 0)
			{
				puts("请先设定迷宫大小！");
				if (getchar())
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
				if (getchar())
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
						if (getchar())
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
				if (getchar())
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
			DFS(start, end, &S, 0);
			if (count == 0)
			{
				system("cls");
				printf("该迷宫无解!\n");
				puts("\n程序已退出，感谢您的使用！\n");
				if (getchar())
					return 0;
			}
			memset(vis, 0, sizeof(vis));
			puts("");
			count = 0;
			fclose(fp);
			puts("\n请按回车返回主菜单\n");
			if (getchar())
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
			if (getchar())
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
			DFS(start, end, &S, 1);
			count = 0;
			StackClear(&S);
			memset(vis, 0, sizeof(vis));
			puts("动态显示完毕！");
			puts("\n请按回车返回主菜单\n");
			if (getchar())
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
			MulDfs(start, end, &S);
			if (count == 10)
				puts("\n已显示10条路径，剩余路径省略！\n");
			count = 0;
			StackClear(&S);
			memset(vis, 0, sizeof(vis));
			puts("\n请按回车返回主菜单\n");
			if (getchar())
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
			BestDfs(start, end, &S, 1);
			if (count < 10)
				printf("一共有%d条最短路；最短的路径长度为%d。\n", count, minlength);
			else
				puts("\n已显示10条最短路，剩余路径省略！\n");
			count = 0;
			StackClear(&S);
			memset(vis, 0, sizeof(vis));
			puts("\n请按回车返回主菜单\n");
			if (getchar())
				break;
		}
		}
	}
}