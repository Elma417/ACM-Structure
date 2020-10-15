#include"SqStack.cpp"
#define _CRT_SECURE_NO_WARNINGS 1   //Visual Studio Scanf会被定义为不安全操作导致无法编译故将安全警告关闭
int M;								//迷宫的宽
int N;								//迷宫的长
int P = 6;  							//随机生成迷宫的路和墙的期望比值
int Maze[20][20], vis[20][20];
int count;							//路径总数
int minlength = 20 * 20;				//目前最小的路径长度
void Random()						//随机生成迷宫的函数
{
	srand(time(NULL));
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i <= M - 1; i++)//按照所给比例生成墙
	{
		for (int j = 0; j <= N - 1; j++)
		{
			if (rand() % 10 > P || i == 0 || j == 0 || i == M - 1 || j == N - 1) Maze[i][j] = 1;
			else Maze[i][j] = 0;
		}
	}
	for (int i = 1; i <= M - 2; i++)			//如果一条路四周都是墙，那么全部打通
	{
		for (int j = 1; j <= N - 2; j++)
		{
			if (Maze[i][j] == 0 && Maze[i + 1][j] == 1 && Maze[i - 1][j] == 1 && Maze[i][j + 1] == 1 && Maze[i][j - 1] == 1) Maze[i + 1][j] = Maze[i - 1][j] = Maze[i][j + 1] = Maze[i][j - 1] = 0;
		}
	}
	for (int i = 0; i <= M - 1; i++)			//地图四周加墙防止越界
	{
		Maze[i][0] = Maze[i][N - 1] = 1;
	}
	for (int j = 0; j <= N - 1; j++)
	{
		Maze[0][j] = Maze[M - 1][j] = 1;
	}
	Maze[1][0] = Maze[1][1] = Maze[M - 2][N - 1] = Maze[M - 2][N - 2] = 0;
	//起点右终点左打通
	for (int i = 1; i <= M - 2; i++)			//如果一条路四周都是路，把这条路堵死，防止路径过多
	{
		for (int j = 1; j <= N - 2; j++)
		{
			if (Maze[i][j] == 0 && Maze[i + 1][j] == 0 && Maze[i - 1][j] == 0 && Maze[i][j + 1] == 0 && Maze[i][j - 1] == 0 && Maze[i + 1][j + 1] == 0 && Maze[i - 1][j - 1] == 0 && Maze[i + 1][j - 1] == 0 && Maze[i - 1][j + 1] == 0) Maze[i][j] = 1;

		}
	}
}