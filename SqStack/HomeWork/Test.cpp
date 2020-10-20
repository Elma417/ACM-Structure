#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "SqStack.cpp"
int M;	   //�Թ��Ŀ�
int N;	   //�Թ��ĳ�
int P = 8; //��������Թ���·��ǽ��������ֵ(P:10-P)
int Maze[20][20], vis[20][20];
int count = 0;			 //·������
int dirr[6];			 //����˳��
int minlength = 20 * 20; //Ŀǰ��С��·������
int opt, opt1, opt2;
void Random() //��������Թ��ĺ���
{
	srand(time(NULL));
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i <= M - 1; i++) //����������������ǽ
		for (int j = 0; j <= N - 1; j++)
			if ((rand() % 10 >= P) || i == 0 || j == 0 || i == M - 1 || j == N - 1)
				Maze[i][j] = 1;
			else
				Maze[i][j] = 0;

	for (int i = 1; i <= M - 2; i++) //���һ��·���ܶ���ǽ����ôȫ����ͨ
		for (int j = 1; j <= N - 2; j++)
			if (Maze[i][j] == 0 && Maze[i + 1][j] == 1 && Maze[i - 1][j] == 1 && Maze[i][j + 1] == 1 && Maze[i][j - 1] == 1)
				Maze[i + 1][j] = Maze[i - 1][j] = Maze[i][j + 1] = Maze[i][j - 1] = 0;

	Maze[1][0] = Maze[1][1] = Maze[M - 2][N - 1] = Maze[M - 2][N - 2] = 0;
	//������յ����ͨ
	for (int i = 1; i <= M - 2; i++) //���һ��·���ܶ���·��������·��������ֹ·������
		for (int j = 1; j <= N - 2; j++)
			if (Maze[i][j] == 0 && Maze[i + 1][j] == 0 && Maze[i - 1][j] == 0 && Maze[i][j + 1] == 0 && Maze[i][j - 1] == 0 && Maze[i + 1][j + 1] == 0 && Maze[i - 1][j - 1] == 0 && Maze[i + 1][j - 1] == 0 && Maze[i - 1][j + 1] == 0)
				Maze[i][j] = 1;
}
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
void DFS(PosType start, PosType end, SqStack* s, int sta)
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
		DFS(nextpos.seat, end, s, sta);
		if (vis[nextpos.seat.x][nextpos.seat.y] != -1)
			vis[nextpos.seat.x][nextpos.seat.y] = 0;
		Pop(s, &nextpos);
	}
}
void MulDfs(PosType start, PosType end, SqStack* s) //�����������·��
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
		MulDfs(nextpos.seat, end, s);
		vis[nextpos.seat.x][nextpos.seat.y] = 0;
		Pop(s, &nextpos);
	}
}
void BestDfs(PosType start, PosType end, SqStack* s, int len) //����������·��
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
		puts("*********************���Ǻ�&�ܽ���*********************");
		puts("                       ��ϷĿ¼");
		puts("                   1.�趨�Թ���С");
		puts("                   2.�Զ������Թ�");
		puts("                   3.�ļ������Թ�");
		puts("                   4.�޸ı���˳��");
		puts("                   5.��̬��ʾ·��");
		puts("                   6.�������·��");
		puts("                   7.������·��");
		puts("                   8.�˳��Թ�����");
		puts("******************************************************");
		printf("����������ѡ��:");
		if (!scanf("%d", &opt) || opt < 1 || opt > 8) //�������
		{
			fflush(stdin);
			puts("����Ƿ������������룡");
			Sleep(1600);
			continue;
		}
		fflush(stdin);
		switch (opt)
		{

		case 8: //8.�˳��Թ�����
		{
			system("cls");
			puts("�������˳���\n��л����ʹ�ã�\n");
			puts("�༶��19184115");
			puts("רҵ:�������ѧ�뼼�����˹�����������ݣ�����ʵ���");
			puts("����:���Ǻ� 19195216         �ĵ�:�ܽ��� 19151135");

			if (getchar())
				return 0;
		}
		case 1: //1.�趨�Թ���С
		{
			memset(choice, 0, sizeof(choice));
			choice[1] = 1;
			while (1)
			{
				system("cls");
				puts("�������Թ��Ŀ�(5~10)��");
				if (scanf("%d", &M) == 0 || M > 10 || M < 5)
				{
					fflush(stdin);
					puts("����Ƿ������������룡");
					Sleep(1600);
					continue;
				}
				break;
			}
			while (1)
			{
				system("cls");
				puts("�������Թ��ĳ�(5~10)��");
				scanf("%d", &N);
				if (N > 10 || N < 5)
				{
					fflush(stdin);
					puts("����Ƿ������������룡");
					Sleep(1600);
					continue;
				}
				break;
			}
			puts("�Թ�������ϣ�\n�밴�س��������˵�");
			start.x = 1;
			start.y = 0;
			end.x = M - 2;
			end.y = N - 1;
			fflush(stdin);
			if (getchar())
				break;
		}
		case 2: //2.�Զ������Թ�
		{
			system("cls");
			if (choice[1] == 0)
			{
				puts("�����趨�Թ���С��");
				Sleep(1600);
				continue;
			}
			choice[2] = 1;
			choice[3] = 0;
			do
			{
				Random();
				DFS(start, end, &S, 0);
			} while (count == 0); //��������Թ�ֱ���Թ���ͨ
			memset(vis, 0, sizeof(vis));
			puts("�Թ����ɳɹ���");
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
			count = 0;
			puts("\n�밴�س��������˵�\n");
			if (getchar())
				break;
		}
		case 3: //3.�ļ������Թ�
		{
			system("cls");
			if (choice[1] == 0)
			{
				puts("�����趨�Թ���С��");
				if (getchar())
					continue;
			}
			choice[2] = 0;
			choice[3] = 1;
			FILE* fp;
			if ((fp = fopen("input.txt", "r")) == NULL)
			{

				system("cls");
				printf("�����ļ�������!\n");
				puts("\n�������˳�����л����ʹ�ã�\n");
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
						printf("�����ļ����Ϸ�!\n");
						puts("\n�������˳�����л����ʹ�ã�\n");
						if (getchar())
							return 0;
					}
				}
			int test = -19195216;
			fscanf(fp, "%d", &test);
			if (test != -19195216)
			{
				system("cls");
				printf("�����ļ����Ϸ�!\n");
				puts("\n�������˳�����л����ʹ�ã�\n");
				if (getchar())
					return 0;
			}
			puts("�Թ���ȡ�ɹ���");
			puts("�����ļ��е��Թ�Ϊ��");
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < N; j++)
					if (Maze[i][j] == 1)
						printf("��");
					else
						printf("��");
				puts("");
			}
			DFS(start, end, &S, 0);
			if (count == 0)
			{
				system("cls");
				printf("���Թ��޽�!\n");
				puts("\n�������˳�����л����ʹ�ã�\n");
				if (getchar())
					return 0;
			}
			memset(vis, 0, sizeof(vis));
			puts("");
			count = 0;
			fclose(fp);
			puts("\n�밴�س��������˵�\n");
			if (getchar())
				break;
		}
		case 4: //4.�޸ı���˳��
		{
			system("cls");
			while (1)
			{
				system("cls");
				puts("���������˳���Ӧ�ı�ţ�1.�� 2.�� 3.�� 4.��");

				puts("�������һ����");
				scanf("%d", &dirr[1]);
				if (dirr[1] != 1 && dirr[1] != 2 && dirr[1] != 3 && dirr[1] != 4)
				{
					fflush(stdin);
					puts("����Ƿ������ٴ����룡\n");
					Sleep(1600);
					continue;
				}

				puts("������ڶ�����");
				scanf("%d", &dirr[2]);
				if ((dirr[2] != 1 && dirr[2] != 2 && dirr[2] != 3 && dirr[2] != 4) || dirr[2] == dirr[1])
				{
					fflush(stdin);
					puts("����Ƿ������ٴ����룡\n");
					Sleep(1600);
					continue;
				}

				puts("�������������");
				scanf("%d", &dirr[3]);
				if ((dirr[3] != 1 && dirr[3] != 2 && dirr[3] != 3 && dirr[3] != 4) || dirr[3] == dirr[2] || dirr[3] == dirr[1])
				{
					fflush(stdin);
					puts("����Ƿ������ٴ����룡\n");
					Sleep(1600);
					continue;
				}

				puts("��������ĸ���");
				scanf("%d", &dirr[4]);
				if ((dirr[4] != 1 && dirr[4] != 2 && dirr[4] != 3 && dirr[4] != 4) || dirr[4] == dirr[3] || dirr[4] == dirr[2] || dirr[4] == dirr[1])
				{
					fflush(stdin);
					puts("����Ƿ������ٴ����룡\n");
					Sleep(1600);
					continue;
				}

				break;
			}
			puts("����˳���޸ĳɹ���");
			puts("\n�밴�س��������˵�\n");
			if (getchar())
				break;
		}
		case 5: //5.��̬��ʾ·��
		{
			system("cls");
			if (choice[1] == 0)
			{
				puts("�����趨�Թ���С��");
				Sleep(1600);
				continue;
			}
			if (choice[2] + choice[3] == 0)
			{
				puts("���� ������� �� ��ȡ�Թ���");
				Sleep(1600);
				continue;
			}
			DFS(start, end, &S, 1);
			count = 0;
			StackClear(&S);
			memset(vis, 0, sizeof(vis));
			puts("��̬��ʾ��ϣ�");
			puts("\n�밴�س��������˵�\n");
			if (getchar())
				break;
		}
		case 6: //6.�������·��
		{
			system("cls");
			if (choice[1] == 0)
			{
				puts("�����趨�Թ���С��");
				Sleep(1600);
				continue;
			}
			if (choice[2] + choice[3] == 0)
			{
				puts("���� ������� �� ��ȡ�Թ���");
				Sleep(1600);
				continue;
			}
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
			MulDfs(start, end, &S);
			if (count == 10)
				puts("\n����ʾ10��·����ʣ��·��ʡ�ԣ�\n");
			count = 0;
			StackClear(&S);
			memset(vis, 0, sizeof(vis));
			puts("\n�밴�س��������˵�\n");
			if (getchar())
				break;
		}
		case 7: //7.������·��
		{
			system("cls");
			if (choice[1] == 0)
			{
				puts("�����趨�Թ���С��");
				Sleep(1600);
				continue;
			}
			if (choice[2] + choice[3] == 0)
			{
				puts("���� ������� �� ��ȡ�Թ���");
				Sleep(1600);
				continue;
			}
			BestDfs(start, end, &S, 1);
			if (count < 10)
				printf("һ����%d�����·����̵�·������Ϊ%d��\n", count, minlength);
			else
				puts("\n����ʾ10�����·��ʣ��·��ʡ�ԣ�\n");
			count = 0;
			StackClear(&S);
			memset(vis, 0, sizeof(vis));
			puts("\n�밴�س��������˵�\n");
			if (getchar())
				break;
		}
		}
	}
}