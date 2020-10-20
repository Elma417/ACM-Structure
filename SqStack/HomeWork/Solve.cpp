#define _CRT_SECURE_NO_WARNINGS 1   //Mazeual Studio Scanf�ᱻ����Ϊ����ȫ���������޷�����ʽ���ȫ����ر�
#include "SqStack.cpp"
#include"CreatPuzzle.cpp"

//������������
//ǽ=0 �߹�=0;

typedef int Status;
Status Judge(PosType e)				//�ж��Ƿ����
{
	if (e.x >= 0 && e.x < M && e.y >= 0 && e.y < N && Maze[e.x][e.y] == 0) return OK;
	return OVERFLOW;
}
PosType NextPos(PosType e, int dir)  //��һ��
{
	PosType E;
	switch (dir)
	{
	case 1:E.x = e.x; E.y = e.y + 1; break;//����
	case 2:E.x = e.x + 1; E.y = e.y; break;//����	
	case 3:E.x = e.x; E.y = e.y - 1; break;//����
	default:E.x = e.x - 1; E.y = e.y;	   //����   
	}
	return E;
}
void PrintPath(SqStack* s)
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
		if (isFirst) isFirst = FALSE;
		else printf("->");
		printf("(%d,%d)", TempValue.seat.x, TempValue.seat.y);
	}
	puts("\n");
}
void PrintMaze()					//��ӡ�Թ�
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Maze[i][j] == 0 && vis[i][j] > 0)
			{
				switch (vis[i][j])
				{
				case 1:printf("��"); break;
				case 2:printf("��"); break;
				case 3:printf("��"); break;
				default:printf("��");
				}
			}
			else if (Maze[i][j] == 1) printf("��");						//�Թ���ǽ
			else if (Maze[i][j] == 0 && vis[i][j] == -1) printf("��");      //��ͨ��·
			else printf("��");										//�Թ�δ�ߵ�·
		}
		puts("");
	}
}
Status DynamicMazePath(PosType start, PosType end, SqStack* s)//��̬��ʾ·��
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
			if (!StackEmpty(*s))
			{
				Pop(s, &e);
				while (e.di == 4 && !StackEmpty(*s))
					//�ĸ������̽����˵����λ���޷�ͨ����Ϊ���� 
				{
					vis[e.seat.x][e.seat.y] = -1;
					Pop(s, &e);
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
	} while (!StackEmpty(*s));
	return FALSE;
}
void dfs(PosType start, PosType end, SqStack* s)				//�����������·��
{
	if (count >= 100) return;
	if (start.x == end.x && start.y == end.y)
	{
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
		if (vis[nextpos.seat.x][nextpos.seat.y] || !Judge(nextpos.seat)) continue;
		vis[start.x][start.y] = i;
		vis[nextpos.seat.x][nextpos.seat.y] = 1;
		Push(s, nextpos);
		dfs(nextpos.seat, end, s);
		vis[nextpos.seat.x][nextpos.seat.y] = 0;
		Pop(s, &nextpos);
	}
}
void dfs2(PosType start, PosType end, SqStack* s, int len)		//����������·��
{
	if (start.x == end.x && start.y == end.y)
	{
		if (len == minlength)
		{
			PrintMaze();
			printf("��%d��·�����ҵ���\n", ++count);
			PrintPath(s);
			puts("");
			return;
		}
		else if (len < minlength)
		{
			minlength = len;
			system("cls");
			puts("������ɵĵ�ͼΪ��");
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < N; j++)
					if (Maze[i][j] == 1) printf("��");
					else printf("��");
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
		if (vis[nextpos.seat.x][nextpos.seat.y] || !Judge(nextpos.seat)) continue;
		vis[start.x][start.y] = i;
		vis[nextpos.seat.x][nextpos.seat.y] = 1;
		Push(s, nextpos);
		dfs2(nextpos.seat, end, s, len + 1);
		vis[nextpos.seat.x][nextpos.seat.y] = 0;
		Pop(s, &nextpos);
	}
}