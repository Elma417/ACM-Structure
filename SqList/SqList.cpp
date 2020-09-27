// Sqlist.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#define _CRT_SECURE_NO_WARNINGS 1   //Visual Studio Scanf会被定义为不安全操作导致无法编译故将安全警告关闭
#define Size 1000
#include <stdio.h>
#include <stdlib.h>
typedef struct Sqlist
{
    int* head;
    int length;
    int listsize;
}Sqlist;
Sqlist EmptyList()
//构造空表
{
    Sqlist t;
    t.head = (int*)malloc(Size * sizeof(int));
    if (!t.head)
    {
        printf("初始化失败请重试\n");
        exit(0);
    }
    t.length = 0;
    t.listsize = Size;
    return t;
}
Sqlist Add(Sqlist t, int elem, int add)
//插入输入的元素
{
    for (int i = t.length - 1; i >= add; i--)  t.head[i + 1] = t.head[i];
    t.head[add] = elem;
    t.length++;
    return t;
}
Sqlist deleteEle(Sqlist t, int position)
//删除相应位置的元素
{
    for (int i = position + 1; i < t.length; i++) t.head[i - 1] = t.head[i];
    t.length--;
    return t;
}
int searchfor(Sqlist t, int elem)
//搜索第一个值为elem的元素返回它的位置
{
    for (int i = 0; i < t.length; i++)
        if (t.head[i] == elem)
            return i;
    return -1;
}
Sqlist change(Sqlist t, int elem, int newElem)
//更改函数，其中，elem为要更改的元素的值，newElem为新的数据元素
{
    int add = searchfor(t, elem);
    t.head[add] = newElem;
    return t;
}
void display(Sqlist t)
//输出顺序表
{
    for (int i = 0; i < t.length; i++) printf("%d ", t.head[i]);
    puts("");
}
int main()
{
    Sqlist L = EmptyList();
    puts("请输入元素个数:");
    scanf("%d", &L.length);
    puts("请输入这些元素");
    for (int i = 0; i < L.length; i++) scanf("%d", &L.head[i]);
    printf("原顺序表：\n");
    display(L);
    printf("请选择功能\n1.删除顺序表中值为key的所有结点\n2.删除顺序表中值重复的结点\n");
    int choice;
    scanf("%d", &choice);
    while (choice != 1 && choice != 2) {
        puts("输入错误请重新输入选项");
        scanf("%d", &choice);
    }
    if (choice == 1)`
    {
        int key;
        printf("请输入key值:\n");
        scanf("%d", &key);
        while (1)
        {
            int now = searchfor(L, key);
            if (now == -1) break;
            L = deleteEle(L, now);
        }
    }
    else if (choice == 2)
    {
        for (int i = 0; i < L.length; i++)
            for (int j = i + 1; j < L.length; j++)
                if (L.head[i] == L.head[j])
                    L = deleteEle(L, i--);
    }
    display(L);
    scanf("%d",choice);
    return 0;
}