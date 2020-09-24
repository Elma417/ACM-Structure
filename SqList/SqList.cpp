// SqList.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#define Size 10000
typedef struct mylist

    int* head;
    int len;
    int size;
}mylist;
mylist Initmylist()
//构造一个空的线性表
{
    mylist t;
    t.head = (int*)malloc(Size * sizeof(int));
    if (!t.head)
    {
        printf("初始化失败\n");
        exit(0);
    }
    t.len = 0;
    t.size = Size;
    return t;
}
mylist addmylist(mylist t, int elem, int add)
//在顺序线性表t中第add位置之前插入新的元素elem
{
    if (add >= t.len || add < 0)
    {
        puts("插入位置不合法");
        return t;
    }
    if (t.len == t.size)
    {
        t.head = (int*)realloc(t.head, (t.size + 1) * sizeof(int));
        if (!t.head)
        {
            puts("存储分配失败");
            exit(0);
        }
        t.size++;
    }
    for (int i = t.len - 1;i >= add;i--)  t.head[i + 1] = t.head[i];
    t.head[add] = elem;
    t.len++;
    return t;
}
mylist delmylist(mylist t, int add)
//在顺序线性表t中删除第add个位置的元素
{
    if (add >= t.len || add < 0)
    {
        printf("被删除元素的位置非法\n");
        return t;
    }
    for (int i = add + 1;i < t.len;i++) t.head[i - 1] = t.head[i];
    t.len--;
    return t;
}
int selectmylist(mylist t, int elem)
//搜索第一个值为elem的元素，并返回它的位置
{
    for (int i = 0;i < t.len;i++)
        if (t.head[i] == elem)
            return i;
    return -1;
}
mylist amendmylist(mylist t, int elem, int newElem)
//更改函数，其中，elem为要更改的元素的值，newElem为新的数据元素
{
    int add = selectmylist(t, elem);
    t.head[add] = newElem;
    return t;
}
void displaymylist(mylist t)
//输出顺序表
{
    for (int i = 0;i < t.len;i++) printf("%d ", t.head[i]);
    puts("");
}
int main()
{
    mylist t1 = Initmylist();
    puts("请输入顺序表内元素的个数:");
    scanf("%d", &t1.len);
    puts("请依次输入这些元素");
    for (int i = 0;i < t1.len;i++) scanf("%d", &t1.head[i]);
    printf("原顺序表：\n");
    displaymylist(t1);
    printf("请选择你要实现的功能\n1.删除顺序表中值为key的所有结点\n2.删除顺序表中值重复的结点\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1)
    {
        int key;
        printf("请输入要删除的key值:\n");
        scanf("%d", &key);
        while (1)
        {
            int now = selectmylist(t1, key);
            if (now == -1) break;
            t1 = delmylist(t1, now);
        }
    }
    else if (choice == 2)
    {
        for (int i = 0;i < t1.len;i++)
            for (int j = i + 1;j < t1.len;j++)
                if (t1.head[i] == t1.head[j])
                    t1 = delmylist(t1, i--);
    }
    else
    {
        puts("输入错误");
        exit(0);
    }

    displaymylist(t1);
    return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
