
#include"CreatPuzzle.cpp"
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