#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MAX 100
#define MAX_SIZE	1024
int count = 1;
typedef struct BiTNode
{
	char data;
	struct BiTNode* lchild;
	struct BiTNode* rchild;
}BiTNode,*BiTree;

typedef struct Quene {						 
	int front;								
	BiTNode* data[MAX_SIZE];					
	int rear;								
}SqQueue; 									 


void CreateBiTree(BiTree* T)
{
	char ch;
	scanf("%c", &ch);
	if (ch == '#')
		*T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		if (!*T)
			return;
		(*T)->data = ch;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
}


void ShowBTree(BiTree t)
{
	if (t)
	{
		printf("%c", t->data);
		if (t->lchild || t->rchild)
		{
			printf("("); count++;
		}
		ShowBTree(t->lchild);
		if (t->rchild)
			if(t->lchild||t->rchild)
			printf(",");
		ShowBTree(t->rchild);
	}
}


void PreOrder(BiTree T)
{
	if (T == NULL)
		return;
	printf("%c ", T->data);
	PreOrder(T->lchild);
	PreOrder(T->rchild);
}


void InOrder(BiTree T)
{
	if (T == NULL)
		return;
	InOrder(T->lchild);
	printf("%c ", T->data);
	InOrder(T->rchild);
}


void PostOrder(BiTree T)
{
	if (T == NULL)
		return;
	PostOrder(T->lchild);
	PostOrder(T->rchild);
	printf("%c ", T->data);
}

void initQueue(SqQueue*& q) 
{
	q = (SqQueue*)malloc(sizeof(SqQueue));	
	q->front = q->rear = -1;				
}

bool emptyQueue(SqQueue*& q) 
{
	if (q->front == q->rear) {				 
		return true;						 
	}
	else {
		return false;						
	}
}


bool enQueue(SqQueue*& q, BiTNode*& BT) 
{
	if (q->rear == MAX_SIZE - 1) {		
		return false;						
	}
	q->rear++;								
	q->data[q->rear] = BT;					 
	return true;							 
}


bool deQueue(SqQueue*& q, BiTNode*& BT)
{
	if (q->front == q->rear) {				 
		return false;						 
	}
	q->front++;								
	BT = q->data[q->front];					 
	return true;							
}


void levelOrder(BiTNode*& BT)
{
	SqQueue* q;
	initQueue(q);
	if (BT != NULL) {
		enQueue(q, BT);
	}
	while (emptyQueue(q) != true) {
		deQueue(q, BT);
		printf("%c", BT->data);
		if (BT->lchild != NULL) {
			enQueue(q, BT->lchild);
		}
		if (BT->rchild != NULL) {
			enQueue(q, BT->rchild);
		}
	}
}


int LeafNum(BiTree T)
{
	if (T == NULL)
		return 0;
	if (T->lchild == NULL && T->rchild == NULL)
		return 1;
	size_t lsize = LeafNum(T->lchild);
	size_t rsize = LeafNum(T->rchild);
	return lsize + rsize;
}


int NodeNum(BiTree T)
{
	if (T == NULL)
		return 0;
	int LeftNum = NodeNum(T->lchild);
	int RightNum = NodeNum(T->rchild);
	int ret = LeftNum + RightNum + 1;
	return ret;
}


int TreeDepth(BiTree T)
{
	int Height = 0;
	if (T == NULL)
		return 0;
	else
	{
		int L_Height = TreeDepth(T->lchild);
		int R_Height = TreeDepth(T->rchild);
		Height = L_Height >= R_Height ? L_Height + 1 : R_Height + 1;
	}
	return Height;
}

void MenuTree() /*显示菜单子函数*/
{
	printf("\n 二叉树子系统");
	printf("\n =================================================");
	printf("\n| 1——建立一个新二叉树 |");
	printf("\n| 2——广义表表示法显示 |");
	printf("\n| 3——先序遍历 |");
	printf("\n| 4——中序遍历 |");
	printf("\n| 5——后序遍历 |");
	printf("\n| 6——层次遍历 |");
	printf("\n| 7——求叶子结点数目 |");
	printf("\n| 8——求二叉树总结点数目 |");
	printf("\n| 9——求树深度 |");
	printf("\n| 0——返回 |");
	printf("\n ================================================");
	printf("\n请输入菜单号（0-9）:");
}
void btree()
{
	BiTree T = NULL;
	char ch1, ch2, a;
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y')
	{
		MenuTree();
		scanf("%c", &ch2);
		getchar();
		switch (ch2)
		{
		case'1':
			printf("请按先序序列输入二叉树的结点：\n");
			printf("说明：输入结点后按回车（'#'表示后继结点为空）：\n");
			printf("请输入根结点：");
			CreateBiTree(&T);
			printf("二叉树成功建立！"); break;
		case  '2':
			printf("二叉树广义表表示法如下：");
			ShowBTree(T); break;
		case  '3':
			printf("二叉树的前序遍历序列为：");
			PreOrder(T); break;
		case  '4':
			printf("二叉树的中序遍历序列为：");
			InOrder(T); break;
		case  '5':
			printf("二叉树的后序遍历序列为：");
			PostOrder(T); break;
		case  '6':
			printf("二叉树的层次遍历序列为：");
			levelOrder(T); break;
		case  '7':
			count = 0; count=LeafNum(T);
			printf("该二叉树有%d个叶子。", count); break;
		case  '8':
			count = 0; count=NodeNum(T);
			printf("该二叉树共有%d个结点", count); break;
		case  '9':
			printf("该二叉树的深度是%d。", TreeDepth(T)); break;
		case  '0':
			ch1 = 'n'; break;
		default:
			printf("输入有误，请输入0-9进行选择！");
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
}
