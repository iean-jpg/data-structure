#pragma once
#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
typedef int ElemType, Status;
typedef struct LNode {
	ElemType data;
	struct LNode* next;
}LNode, * LinkList;


Status InitList(LinkList& L)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	return OK;
}

Status CreateList_H(LinkList& L, int n)
{
	L = (LinkList)malloc(sizeof(LNode));
	LNode* s;
	L->next = NULL;
	int i;
	ElemType ele;
	for (i = 0; i < n; i++)
	{
		scanf("%d", &ele);
		s = (LNode*)malloc(sizeof(LNode));
		s->data = ele;
		s->next = L->next;
		L->next = s;
	}
	return OK;
}


Status CreateList_T(LinkList& L, int n)
{
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	LNode* s;
	LNode* r = L;
	int i;
	ElemType ele;
	for (i = 0; i < n; i++)
	{
		scanf("%d", &ele);
		s = (LNode*)malloc(sizeof(LNode));
		s->data = ele;
		r->next = s;
		r = s;
	}
	r->next = NULL;
	return OK;
}

int Linklength(LinkList L)
{
	int k = 1;
	while (L != NULL)
	{
		k++;
		L = L->next;
	}
	return k;
}


LNode* GetList_Elem(LinkList L, ElemType find_ele)
{
	LNode* node = L->next;
	while (node != NULL && node->data != find_ele)
	{
		node = node->next;
	}
	return node;
}


LNode* GetList_Pos(LinkList L, int pos)
{
	if (pos == 0)
	{
		return L;
	}
	if (pos < 1)
	{
		return NULL;
	}
	LNode* node = L;
	int j = 0;
	while (node && j < pos)
	{

		node = node->next;
		j++;
	}
	if (node == NULL)
	{
		printf("线性表为空");
		return NULL;
	}
	return node;
}


Status InserElem(LinkList& L, int pos, ElemType inser_ele)
{
	LNode* node;
	LNode* new_node = (LNode*)malloc(sizeof(LNode));
	new_node->data = inser_ele;
	node = GetList_Pos(L, pos - 1);
	new_node->next = node->next;
	node->next = new_node;
	return OK;
}


Status DeleteElem(LinkList& L, int pos)
{	
	LinkList p,q;
	int j;
	p = L;
	j = 0;
	while ((p->next) && (j < (pos - 1)))
	{
		p = p->next;
		++j;
	}
	if (!(p->next) || j > (pos - 1))return ERROR;
	q = p->next;
	p->next = q->next;
	free(q);
	return OK;
}

//���
void PrintList(LinkList L)
{
	LNode* node = L->next;
	while (node != NULL)
	{
		printf("%d\t", node->data);
		node = node->next;
	}
	printf("\n\n");
}

//�ϲ�
void MergeList(LinkList& LA, LinkList& LB, LinkList& LC)
{
	LNode* anode = LA->next;
	LNode* bnode = LB->next;
	LNode* cnode;
	LC = cnode = LA;
	while (anode != NULL && bnode != NULL)
	{
		if (anode->data <= bnode->data)
		{
			cnode->next = anode;
			cnode = anode;
			anode = anode->next;
		}
		else
		{
			cnode->next = bnode;
			cnode = bnode;
			bnode = bnode->next;
		}
	}
	cnode->next = anode ? anode : bnode;
	free(LB);
}

void MenuLine()
{ /*显示菜单子函数*/
	printf("\n 线性表子系统");
	printf("\n =================================================");
	printf("\n| 1——建立 |");
	printf("\n| 2——插入 |");
	printf("\n| 3——删除 |");
	printf("\n| 4——按位置查找 |");
	printf("\n| 5——按元素值查找 |");
	printf("\n| 6——求表长 |");
	printf("\n| 0——返回 |");
	printf("\n =================================================");
	printf("\n请输入菜单号（0-6）:");
}

void linklist()
{
	LNode* node;
	LinkList head = NULL;
	ElemType x;
	int i, n;
	char ch1, ch2, a;
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y')
	{
		MenuLine();
		scanf("%c", &ch2);
		switch (ch2)
		{
		case'1':
			InitList(head);
			printf("请输入要建立线性表的长度：");
			scanf("%d", &n); 
			printf("输入%d个元素，用空格隔开：",n);
			CreateList_T(head, n);
			printf("建立后的线性表为：\n");
			PrintList(head);
			break;
		case'2':
			printf("请输入要插入的元素位置：");
			scanf("%d", &i);
			printf("请输入要插入的元素值：");
			scanf("%d", &x); 
			InserElem(head, i, x);
			printf("插入后的线性表为：\n", x);
			PrintList(head);
			break;
		case '3':
			printf("请输入要删除的元素位置：");
			scanf("%d", &i); 
			DeleteElem(head, i);
			printf("删除第%d位的元素后的线性表为：\n", i);
			PrintList(head);
			break;
		case '4':
			printf("请输入查找的元素位置（大于等于1的整数）：");
			scanf("%d", &i); 
			node=GetList_Pos(head, i);
			printf("元素为：%d", node->data);
			break;
		case '5':
			printf("请输入查找的整数：");
			scanf("%d", &x);
			if (GetList_Elem(head,x))
				printf("该元素存在");
			else
				printf("该元素不存在");
			break;
		case '6':
			printf("该线性表的长度为%d！", Linklength(head));
			break;
		case '0':
			ch1 = 'n'; break;
		default:
			printf("输入有误，请输入0-6进行选择！");
		}
	}
	if (ch2 != '0')
	{
		printf("\n按回车键继续，按任意键返回主菜单！\n");
		a = getchar();
		if (a != '\xA')
		{
			getchar(); ch1 = 'n';
		}
	}
}
