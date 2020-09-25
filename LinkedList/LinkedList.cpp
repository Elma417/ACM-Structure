#define _CRT_SECURE_NO_WARNINGS 1   //Visual Studio Scanf会被定义为不安全操作导致无法编译故将安全警告关闭
#include <stdio.h>
#include <stdlib.h>
#define Size 1000
typedef struct LinkList
//创造链表结构体
{
	int elem;
	struct LinkList *next;
}LinkList;
LinkList *initLink()
//建立链表
{
	LinkList *p = (LinkList*)malloc(sizeof(LinkList));//头节点
	LinkList *temp = p;//指向头节点的指针
	for (int i = 1; i < Size; i++)
	{
		LinkList* a = (LinkList*)malloc(sizeof(LinkList));
		a->elem = i;
		a->next = NULL;
		temp->next = a;
		temp = temp->next;
	}
	return p;
}
LinkList* insertElem(LinkList *t, int elem, int position)
//实现数据插入链表
{
	LinkList *temp = t;
	for (int i = 1; i < position ; i++)
	{
		temp = temp->next;
		if (temp->next == NULL)
		{
			printf("插入的位置非法请确认后重新输入");
			return t;
		}
	}
	//若位置合法 则创建新节点c
	LinkList* c = (LinkList*)malloc(sizeof(LinkList));
	c->elem = elem;
	c->next = temp->next;
	temp->next = c;
	return t;
}
LinkList* DeleteElem(LinkList* t, int position)
//删除相应位置的元素
{
	
}