#define _CRT_SECURE_NO_WARNINGS 1   //Visual Studio Scanf会被定义为不安全操作导致无法编译故将安全警告关闭
#define Size 1000
#include <stdio.h>
#include <stdlib.h>
typedef struct LinkList
//创造链表结构体
{
	int elem;
	struct LinkList* next;
}LinkList;
LinkList* initLink()
//建立链表
{
	LinkList* p = (LinkList*)malloc(sizeof(LinkList));//头节点
	LinkList* temp = p;//指向头节点的指针
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
LinkList* insertElem(LinkList* t, int elem, int position)
//实现数据插入链表
{
	LinkList* temp = t;
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
	LinkList* temp = t;
	for (int i = 1; i < position; i++)
	//寻找应删除的节点上一个节点
	{
		temp = temp->next;
		if(temp->next==NULL)
		{
			printf("不存在该位置的节点");
			return t;
		}
	}
	LinkList* del = temp->next;
	temp->next = del->next;
	free(del);
	return t;
}
LinkList* ChangeElem(LinkList* t, int elem, int position)
//修改节点
{
	LinkList* temp = t;
	temp = temp->next;
	for (int i = 1; i < position; i++)
	{
		temp = temp->next;
	}
	temp->elem = elem;
	return t;
}
int SearchElem(LinkList* t, int elem)
//寻找值为elem的节点
{
	LinkList* temp = t;
	int position;
	while (temp->next)
	{
		temp = temp->next;
		if (temp->elem == elem)return position;
		position++;
	}
	return -1;
}
void display(LinkList* t)
{
	LinkList* temp = t;
	while (temp->next)
	{
		temp = temp->next;
		printf("%d", temp->elem);
	}
	printf("\n");
}
int main()
{
	
}