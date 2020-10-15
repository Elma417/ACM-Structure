#include<time.h>
#include<windows.h>
#include"Solve.cpp"
int main()
{
	while (1)
	{
		puts("�������Թ��Ŀ�(5~10)��");
		scanf("%d", &M);
		if (M > 10 || M < 5)
		{
			puts("����Ƿ������������룡");
			continue;
		}
		break;
	}
	while (1)
	{
		puts("�������Թ��ĳ�(5~10)��");
		scanf("%d", &N);
		if (N > 10 || N < 5)
		{
			puts("����Ƿ������������룡");
			continue;
		}
		break;
	}
	int opt, opt2;
	while (1)
	{
		puts("��ѡ���Թ������ɷ�ʽ��\n1.�Զ�����\n2.�ļ�����");
		scanf("%d", &opt);
		if (opt != 1 && opt != 2)
		{
			puts("����Ƿ������ٴ����룡");
			continue;
		}
		break;
	}
	while (1)
	{
		puts("��ѡ������·���ķ�ʽ��\n1.��̬��ʾһ��\n2.����·��\n3.���·��");
		scanf("%d", &opt2);
		if (opt2 != 1 && opt2 != 2 && opt2 != 3)
		{
			puts("����Ƿ������ٴ����룡");
			continue;
		}
		break;
	}
	SqStack S;
	PosType start, end;
	start.x = 1; start.y = 0;			//�������
	end.x = M - 2; end.y = N - 1;			//�յ�����

	if (opt == 1) Random();			//���ɵ�ͼ
	else							//��ȡ��ͼ
	{
		freopen("input.txt", "r", stdin);
		for (int i = 0; i <= M - 1; i++)
			for (int j = 0; j <= N - 1; j++)
				scanf("%d", &Maze[i][j]);
	}

	if (opt2 == 1)						//��̬��ʾһ��·��
	{
		while (!DynamicMazePath(start, end, &S))
		{
			puts("������ɵ��Թ��޽⣡\n���ڰ����������ɣ�\n");
			Sleep(100);
			system("cls");
			Random();
		}
		puts("�ҵ�·��:");
		PrintPath(&S);
		puts("");
	}

	else if (opt2 == 2)				//��ʾ����·��
	{
		P = 1;
		if (opt == 1)
		{
			puts("������ɵĵ�ͼΪ��");
			PrintMaze();
			puts("");
		}
		InitStack(&S);
		count = 0;
		while (1)					//��ֹû��·�������
		{
			SElemType now;
			now.seat = start;
			Push(&S, now);
			dfs(start, end, &S);
			if (count == 0)
			{
				if (opt == 2)
				{
					puts("�������ļ��ڵ��Թ��޽⣡");
					break;
				}
				puts("������ɵ��Թ��޽⣡\n���ڰ����������ɣ�\n");
				Sleep(1000);
				system("cls");
				Random();
				puts("������ɵĵ�ͼΪ��");
				PrintMaze();
				puts("");
				continue;
			}
			if (count == 100) puts("����ʾ100��·����ʣ��·��ʡ�ԣ�\n");
			break;
		}
	}

	else							//��ʾ���·��
	{
		if (opt == 1)
		{
			puts("������ɵĵ�ͼΪ��");
			PrintMaze();
			puts("");
		}
		InitStack(&S);
		count = 0;
		while (1)					//��ֹû��·�������
		{
			SElemType now;
			now.seat = start;
			Push(&S, now);
			dfs2(start, end, &S, 1);
			if (count == 0)
			{
				if (opt == 2)
				{
					puts("�������ļ��ڵ��Թ��޽⣡");
					break;
				}
				puts("������ɵ��Թ��޽⣡\n���ڰ����������ɣ�\n");
				Sleep(100);
				system("cls");
				Random();
				puts("������ɵĵ�ͼΪ��");
				PrintMaze();
				puts("");
				continue;
			}
			printf("һ����%d�����·����̵�·������Ϊ%d��\n", count, minlength);
			break;
		}
	}
	puts("");
	system("pause");

	return 0;
}
