#define _CRT_SECURE_NO_WARNINGS 1   //Visual Studio Scanf会被定义为不安全操作导致无法编译故将安全警告关闭
#define Size 1
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
	p->next = NULL;
	/*
	LinkList* temp = p;//指向头节点的指针

	for (int i = 1; i < Size; i++)
	{
		LinkList* a = (LinkList*)malloc(sizeof(LinkList));
		a->elem = i;
		a->next = NULL;
		temp->next = a;
		temp = temp->next;
	}
	*/
	return p;
}
LinkList* insertElem(LinkList* t, int elem, int position)
//实现数据插入链表
{
	LinkList* temp = t;
	for (int i = 1; i <position ; i++)
	{
		if (temp->next == NULL)
		{
			printf("插入的位置非法请确认后重新输入\n");
			return t;
		}
		temp = temp->next;
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
	int position=1;
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
		printf("%d ", temp->elem);
	}
	printf("\n");
}
int main()
{
	LinkList* L = initLink();
	puts("请输入元素个数:");
	int Length;
	scanf("%d", &Length);

	puts("请输入这些元素");



	for(int i=1;i<=Length;i++)
	{
		int Newelem=0;
		scanf("%d", &Newelem);
		L = insertElem(L, Newelem, i);
		
	}
	printf("输入的原表为：\n");
	display(L);
	printf("请选择功能\n1.删除顺序表中值为key的所有结点\n2.删除顺序表中值重复的结点\n");
	int choice;
	scanf("%d", &choice);
	while (choice != 1 && choice != 2) {
		puts("输入错误请重新输入选项");
		scanf("%d", &choice);
	}
	if (choice == 1)
	{
		int key;
		printf("请输入key值:\n");
		scanf("%d", &key);
		while (1)
		{
			int now = SearchElem(L, key);
			if (now == -1) break;
			L = DeleteElem(L, now);
		}
	}

	else if (choice == 2)
	{
		LinkList* now = L;
		while (now->next)
		{
			LinkList* temp = now->next;
			while (temp->next)
			{
				if (temp->next->elem == now->next->elem)
				{
					LinkList* del = now->next;
					now->next = now->next->next;
					free(del);
					temp = now->next;
					continue;
				}
				else temp = temp->next;
			}
			now = now->next;
		}
	}
	display(L);
	scanf("%d", choice);
	return 0;
}