#pragma once
#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define Ok 1
typedef int QElemtype,Status;

typedef struct QNode
{
	QElemtype data;
	struct QNode* next;
}QNode,*QueuePtr;

typedef struct
{
	QueuePtr front,rear;
}LinkQueue;


Status InitLinkQueue(LinkQueue* q)
{
	if (!q)
	{
		return ERROR;
	}
	QNode* node = (QNode*)malloc(sizeof(QNode));
	node->next = NULL;
	q->front = q->rear = node;
	return Ok;
}


Status EmptyQueue(LinkQueue* q)
{
	if (!q)
	{
		return ERROR;
	}
	if (q->front = q->rear)
	{
		return Ok;
	}
	return ERROR;
}

Status InQueue(LinkQueue* q, QElemtype e)
{
	if (!q)
	{
		return ERROR;
	}
	QNode* node = (QNode*)malloc(sizeof(QNode));
	if (!node)
	{
		return ERROR;
	}
	node->next = NULL;
	node->data = e;
	q->rear->next = node;
	q->rear = node;
	return Ok;
}


Status DeQueue(LinkQueue* q, QElemtype* e)
{
	if (!q)
	{
		return ERROR;
	}
	QNode* node = q->front->next;
	*e = node->data;
	q->front->next = node->next;
	if (node = q->rear)
	{
		q->rear = q->front;
	}
	return Ok;
}


void GetFront(LinkQueue q,QElemtype* x)
{
	QueuePtr p = q.front->next;
	if (p)
	{
		*x = p->data;
	}

}


void ShowQueue(LinkQueue* q)
{
	if (!q)
		return;
	QNode* node = q->front->next;
	while (node)
	{
		printf("%d\t", node->data);
		node = node->next;
	}
	printf("\n");
}

void MenuQueue()
{ /*显示菜单子函数*/
	printf("\n 队列子系统");
	printf("\n =================================================");
	printf("\n| 1——初始化队列 |");
	printf("\n| 2——入队操作 |");
	printf("\n| 3——出队操作 |");
	printf("\n| 4——求队头元素 |");
	printf("\n| 5——显示队中所有元素 |");
	printf("\n| 0——返回 |");
	printf("\n =================================================");
	printf("\n请输入菜单号（0-5）:");
}

void linkqueue()
{
	int i, n, flag;
	LinkQueue Q;
	QElemtype x;
	char  ch1, ch2, a;
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y')
	{
		MenuQueue();
		scanf("%c", &ch2);
		getchar();
		switch (ch2)
		{
		case  '1':
			flag=InitLinkQueue(&Q);
			if (flag == 1)
				printf("初始化成功");
			else
				printf("初始化失败");
			break;
		case  '2':
			printf("请输入要入队的元素个数：");
			scanf("%d", &n);
			printf("请输入%d个整数进行入队：", n);
			for (i = 0; i < n; i++)
			{
				scanf("%d", &x);
				InQueue(&Q, x);
			}
			printf("入队操作完成");
			break;
		case  '3':
			printf("请输入要出队的元素个数：");
			scanf("%d", &n);
			printf("出队的元素顺序依次为：");
			for (i = 0; i < n; i++)
			{
				flag = DeQueue(&Q, &x);
				printf("%5d", x);
			}
			if (flag == 1)
				printf("\n出队操作成功!");
			else
				printf("\n出队操作失败！");
			break;
		case  '4':
		    GetFront(Q,&x);
			printf("当前的队头元素值为：%d", x);
			break;
		case  '5':
			ShowQueue(&Q);
			break;
		case  '0':
			ch1 = 'n'; break;
		default:
			printf("输入有误，请输入0-4进行选择！");
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