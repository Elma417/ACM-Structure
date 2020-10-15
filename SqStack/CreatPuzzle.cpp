#include"SqStack.cpp"
#define _CRT_SECURE_NO_WARNINGS 1   //Visual Studio Scanf�ᱻ����Ϊ����ȫ���������޷�����ʽ���ȫ����ر�
int M;								//�Թ��Ŀ�
int N;								//�Թ��ĳ�
int P = 6;  							//��������Թ���·��ǽ��������ֵ
int Maze[20][20], vis[20][20];
int count;							//·������
int minlength = 20 * 20;				//Ŀǰ��С��·������
void Random()						//��������Թ��ĺ���
{
	srand(time(NULL));
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i <= M - 1; i++)//����������������ǽ
	{
		for (int j = 0; j <= N - 1; j++)
		{
			if (rand() % 10 > P || i == 0 || j == 0 || i == M - 1 || j == N - 1) Maze[i][j] = 1;
			else Maze[i][j] = 0;
		}
	}
	for (int i = 1; i <= M - 2; i++)			//���һ��·���ܶ���ǽ����ôȫ����ͨ
	{
		for (int j = 1; j <= N - 2; j++)
		{
			if (Maze[i][j] == 0 && Maze[i + 1][j] == 1 && Maze[i - 1][j] == 1 && Maze[i][j + 1] == 1 && Maze[i][j - 1] == 1) Maze[i + 1][j] = Maze[i - 1][j] = Maze[i][j + 1] = Maze[i][j - 1] = 0;
		}
	}
	for (int i = 0; i <= M - 1; i++)			//��ͼ���ܼ�ǽ��ֹԽ��
	{
		Maze[i][0] = Maze[i][N - 1] = 1;
	}
	for (int j = 0; j <= N - 1; j++)
	{
		Maze[0][j] = Maze[M - 1][j] = 1;
	}
	Maze[1][0] = Maze[1][1] = Maze[M - 2][N - 1] = Maze[M - 2][N - 2] = 0;
	//������յ����ͨ
	for (int i = 1; i <= M - 2; i++)			//���һ��·���ܶ���·��������·��������ֹ·������
	{
		for (int j = 1; j <= N - 2; j++)
		{
			if (Maze[i][j] == 0 && Maze[i + 1][j] == 0 && Maze[i - 1][j] == 0 && Maze[i][j + 1] == 0 && Maze[i][j - 1] == 0 && Maze[i + 1][j + 1] == 0 && Maze[i - 1][j - 1] == 0 && Maze[i + 1][j - 1] == 0 && Maze[i - 1][j + 1] == 0) Maze[i][j] = 1;

		}
	}
}