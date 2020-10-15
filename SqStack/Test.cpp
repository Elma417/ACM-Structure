#include<time.h>
#include<windows.h>
#include"Solve.cpp"
int main()
{
	while (1)
	{
		puts("请输入迷宫的宽(5~10)：");
		scanf("%d", &M);
		if (M > 10 || M < 5)
		{
			puts("输入非法，请重新输入！");
			continue;
		}
		break;
	}
	while (1)
	{
		puts("请输入迷宫的长(5~10)：");
		scanf("%d", &N);
		if (N > 10 || N < 5)
		{
			puts("输入非法，请重新输入！");
			continue;
		}
		break;
	}
	int opt, opt2;
	while (1)
	{
		puts("请选择迷宫的生成方式：\n1.自动生成\n2.文件导入");
		scanf("%d", &opt);
		if (opt != 1 && opt != 2)
		{
			puts("输入非法！请再次输入！");
			continue;
		}
		break;
	}
	while (1)
	{
		puts("请选择生成路径的方式：\n1.动态显示一条\n2.多条路径\n3.最短路径");
		scanf("%d", &opt2);
		if (opt2 != 1 && opt2 != 2 && opt2 != 3)
		{
			puts("输入非法！请再次输入！");
			continue;
		}
		break;
	}
	SqStack S;
	PosType start, end;
	start.x = 1; start.y = 0;			//起点坐标
	end.x = M - 2; end.y = N - 1;			//终点坐标

	if (opt == 1) Random();			//生成地图
	else							//读取地图
	{
		freopen("input.txt", "r", stdin);
		for (int i = 0; i <= M - 1; i++)
			for (int j = 0; j <= N - 1; j++)
				scanf("%d", &Maze[i][j]);
	}

	if (opt2 == 1)						//动态显示一条路径
	{
		while (!DynamicMazePath(start, end, &S))
		{
			puts("随机生成的迷宫无解！\n正在帮你重新生成！\n");
			Sleep(100);
			system("cls");
			Random();
		}
		puts("找到路径:");
		PrintPath(&S);
		puts("");
	}

	else if (opt2 == 2)				//显示所有路径
	{
		P = 1;
		if (opt == 1)
		{
			puts("随机生成的地图为：");
			PrintMaze();
			puts("");
		}
		InitStack(&S);
		count = 0;
		while (1)					//防止没有路径的情况
		{
			SElemType now;
			now.seat = start;
			Push(&S, now);
			dfs(start, end, &S);
			if (count == 0)
			{
				if (opt == 2)
				{
					puts("您输入文件内的迷宫无解！");
					break;
				}
				puts("随机生成的迷宫无解！\n正在帮你重新生成！\n");
				Sleep(1000);
				system("cls");
				Random();
				puts("随机生成的地图为：");
				PrintMaze();
				puts("");
				continue;
			}
			if (count == 100) puts("已显示100条路径，剩余路径省略！\n");
			break;
		}
	}

	else							//显示最短路径
	{
		if (opt == 1)
		{
			puts("随机生成的地图为：");
			PrintMaze();
			puts("");
		}
		InitStack(&S);
		count = 0;
		while (1)					//防止没有路径的情况
		{
			SElemType now;
			now.seat = start;
			Push(&S, now);
			dfs2(start, end, &S, 1);
			if (count == 0)
			{
				if (opt == 2)
				{
					puts("您输入文件内的迷宫无解！");
					break;
				}
				puts("随机生成的迷宫无解！\n正在帮你重新生成！\n");
				Sleep(100);
				system("cls");
				Random();
				puts("随机生成的地图为：");
				PrintMaze();
				puts("");
				continue;
			}
			printf("一共有%d条最短路；最短的路径长度为%d。\n", count, minlength);
			break;
		}
	}
	puts("");
	system("pause");

	return 0;
}
