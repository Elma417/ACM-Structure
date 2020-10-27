#include"CreatPuzzle.cpp"
Status Judge(PosType e) //�ж��Ƿ����
{
	if (e.x >= 0 && e.x < M && e.y >= 0 && e.y < N && Maze[e.x][e.y] == 0 && vis[e.x][e.y] == 0)
		return OK;
	return OVERFLOW;
}
PosType NextPos(PosType e, int dir) //��һ��
{
	PosType E;
	switch (dirr[dir])
	{
	case 1:
		E.x = e.x;
		E.y = e.y + 1;
		break; //����
	case 2:
		E.x = e.x + 1;
		E.y = e.y;
		break; //����
	case 3:
		E.x = e.x;
		E.y = e.y - 1;
		break; //����
	default:
		E.x = e.x - 1;
		E.y = e.y; //����
	}
	return E;
}
void PrintPath(SqStack* s) //��ӡ·��
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
void PrintMaze() //��ӡ�Թ�
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
					printf("��");
					break;
				case 2:
					printf("��");
					break;
				case 3:
					printf("��");
					break;
				case 4:
					printf("��");
				}
			}
			else if (vis[i][j] == -1)
				printf("��"); //��ͨ��·
			else if (Maze[i][j] == 1)
				printf("��"); //�Թ���ǽ
			else
				printf("��"); //�Թ�δ�ߵ�·
		}
		puts("");
	}
}
void DynamicDFS(PosType start, PosType end, SqStack* s, int sta)
//sta=0ʱ,����Ƿ��ͨ��sta=1ʱ���������·��
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
			puts("�ҵ�·��:");
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
		DynamicDFS(nextpos.seat, end, s, sta);
		if (vis[nextpos.seat.x][nextpos.seat.y] != -1)
			vis[nextpos.seat.x][nextpos.seat.y] = 0;
		Pop(s, &nextpos);
	}
}
void MultipleDfs(PosType start, PosType end, SqStack* s) //�����������·��
{
	if (count >= 10)
		return;
	if (start.x == end.x && start.y == end.y)
	{
		vis[end.x][end.y] = 5;
		PrintMaze();
		printf("��%d��·�����ҵ���\n", ++count);
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
		MultipleDfs(nextpos.seat, end, s);
		vis[nextpos.seat.x][nextpos.seat.y] = 0;
		Pop(s, &nextpos);
	}
}
void OptimalDfs(PosType start, PosType end, SqStack* s, int len) //����������·��
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
				printf("��%d��·�����ҵ���\n", count);
				PrintPath(s);
				puts("");
			}
			return;
		}
		else if (len < minlength)
		{
			minlength = len;
			system("cls");
			puts("������ɵ��Թ�Ϊ��");
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < N; j++)
					if (Maze[i][j] == 1)
						printf("��");
					else
						printf("��");
				puts("");
			}
			puts("\n");
			count = 1;
			PrintMaze();
			printf("��%d��·�����ҵ���\n", count);
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
		OptimalDfs(nextpos.seat, end, s, len + 1);
		vis[nextpos.seat.x][nextpos.seat.y] = 0;
		Pop(s, &nextpos);
	}
}