#define _CRT_SECURE_NO_WARNINGS 1   //Visual Studio Scanf�ᱻ����Ϊ����ȫ���������޷�����ʽ���ȫ����ر�
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include"Solve.cpp"

//�����û�����Ľ���
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
	//		puts("                       ��ϷĿ¼");
		puts("------------1.�趨�Թ���С------------");
		puts("------------2.�Զ������Թ�------------");
		puts("------------3.�ļ������Թ�------------");
		puts("------------4.�޸ı���˳��------------");
		puts("------------5.��̬��ʾ·��------------");
		puts("------------6.�������·��------------");
		puts("------------7.������·��------------");
		puts("------------8.�˳��Թ�����------------");
		puts("---------------------------------------");
		printf("����������ѡ��:");
		int opt;
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
			puts("�������ܽ���");

			system("PAUSE");
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
			system("PAUSE");
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
				DynamicDFS(start, end, &S, 0);
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
			system("PAUSE");
				break;
		}
		case 3: //3.�ļ������Թ�
		{
			system("cls");
			if (choice[1] == 0)
			{
				puts("�����趨�Թ���С��");
				system("PAUSE");
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
						printf("�����ļ����Ϸ�!\n");
						puts("\n�������˳�����л����ʹ�ã�\n");
						system("PAUSE");
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
				system("PAUSE");
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
			DynamicDFS(start, end, &S, 0);
			if (count == 0)
			{
				system("cls");
				printf("���Թ��޽�!\n");
				puts("\n�������˳�����л����ʹ�ã�\n");
				system("PAUSE");
					return 0;
			}
			memset(vis, 0, sizeof(vis));
			puts("");
			count = 0;
			fclose(fp);
			puts("\n�밴�س��������˵�\n");
			system("PAUSE");
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
			system("PAUSE");
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
			DynamicDFS(start, end, &S, 1);
			count = 0;
			StackClear(&S);
			memset(vis, 0, sizeof(vis));
			puts("��̬��ʾ��ϣ�");
			puts("\n�밴�س��������˵�\n");
			system("PAUSE");
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
			MultipleDfs(start, end, &S);
			if (count == 10)
				puts("\n����ʾ10��·����ʣ��·��ʡ�ԣ�\n");
			count = 0;
			StackClear(&S);
			memset(vis, 0, sizeof(vis));
			puts("\n�밴�س��������˵�\n");
			system("PAUSE");
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
			OptimalDfs(start, end, &S, 1);
			if (count < 10)
				printf("һ����%d�����·����̵�·������Ϊ%d��\n", count, minlength);
			else
				puts("\n����ʾ10�����·��ʣ��·��ʡ�ԣ�\n");
			count = 0;
			StackClear(&S);
			memset(vis, 0, sizeof(vis));
			puts("\n�밴�س��������˵�\n");
			system("PAUSE");
				break;
		}
		}
	}
}