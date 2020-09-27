#define _CRT_SECURE_NO_WARNINGS 1   //Visual Studio Scanf会被定义为不安全操作导致无法编译故将安全警告关闭
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include "SqStack.cpp"
#include"CreatPuzzle.cpp"
int main()
{
	Draw();
	getchar();
	return 0;
}