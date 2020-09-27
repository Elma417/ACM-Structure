// Sqlist.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#define _CRT_SECURE_NO_WARNINGS 1   //Visual Studio Scanf会被定义为不安全操作导致无法编译故将安全警告关闭
#define Size 1000				
#define Stackincrement 10//存储空间分配增量
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
typedef struct  SqStack
{
	int *Bottom;
	int *Top;
	int StackSize;
}SqStack;
SqStack InitStack() 
{
	SqStack S;
	S.Bottom = (int*)malloc(Size * sizeof(SqStack*));
	if (!S.Bottom)	exit(OVERFLOW);//超过 分配失败
	S.Top = S.Bottom;    // 栈空时栈顶和栈底指针相同
	S.StackSize = Size;
	return S;
}
SqStack Push(SqStack S, int elem)
{//入栈
	if (S.Top - S.Bottom >= S.StackSize)//上溢增加空间
	{
		S.Bottom = (int*)realloc(S.Bottom, (S.StackSize + Stackincrement) * sizeof(SqStack*));
		if (!S.Bottom)exit(OVERFLOW);
		S.Top = S.Bottom + S.StackSize;
		S.StackSize += Stackincrement;
	}
	*S.Top++ = elem;
	return S;
}
SqStack Pop(SqStack S) 
{
	//出栈
	if (S.Top == S.Bottom)exit(OVERFLOW);
	printf("%d", *--S.Top);
	return S;
}
bool StackEmpty(SqStack S)
//是否为空栈
{
	if (S.Bottom == S.Top)return 1;
	else return 0;
}
void Display(SqStack S)
{
	while (!StackEmpty(S))
	{
		S=Pop(S);
		puts("");
	}
}
/*Test堆栈是否正常
int main()
{
	
	SqStack S = InitStack();
	int	elem,size;
	printf("请输入元素个数\n");
	scanf("%d", &size);
	for (int i = 1; i <= size; i++)
	{
		printf("请输入第%d个元素:\n", i);
		scanf("%d", &elem);
		if (i == size)puts("\n");
		S=Push(S, elem);
	}
	Display(S);
	

	getchar();
	return 0;
}
*/
