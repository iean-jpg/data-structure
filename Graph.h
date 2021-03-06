#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MaxVex 100

typedef int VertexType;
typedef int EdgeType;
int visited[MaxVex]; /*全局变量，访问数组*/


typedef struct EdgeNode //边表结点
{
	int adjvex; //邻接点域，存储邻接顶点对应的下标
	EdgeType weight; //用于存储权值，对于非网图可以不需要
	struct EdgeNode* next; //链域，指向下一个邻接点
}EdgeNode;
typedef struct VertexNode  //顶点表结点
{
	VertexType data;  //顶点域，存储顶点信息
	EdgeNode* firstedge; //边表头指针
}VertexNode, AdjList[MaxVex];

typedef struct
{
	AdjList adjList;
	int numVertexes, numEdges; //图中当前顶点数和边数
}GraphAdjList;


void CreateAGraph(GraphAdjList* g, int flag)
{ /*生成无向图的邻接表函数*/
	int i, j, k;
	EdgeNode* p;
	if (flag == 0)
		printf("\n===========将建立一个无向图===========\n");
	else
		printf("\n===========将建立一个有向图===========\n");
	printf("请输入图的顶点数：");
	scanf("%d", &g->numVertexes);
	printf("请输入图的边数：");
	scanf("%d", &g->numEdges);
	printf("\n请输入图的各顶点信息：\n");
	for (i = 0; i < g->numVertexes; i++) /*生成有n个顶点的顶点表*/
	{ //getchar(); /*接受上次输入的换行符*/
		printf("第%d个顶点信息：", i + 1);
		scanf("\n%c", &(g->adjList[i].data)); /*读入顶点信息*/
		g->adjList[i].firstedge = NULL; /*点的边表头指针设为空*/
	}
	printf("\n请输入边的信息，输入格式为:序号1，序号2（序号依次为0、1、2...）：\n");
	for (k = 0; k < g->numEdges; k++)
	{
		printf("请输入第%d条边：", k);
		scanf("\n%d,%d", &i, &j);
		/*将编号为i的结点添加到邻接表中*/
		p = (EdgeNode*)malloc(sizeof(EdgeNode));
		p->adjvex = j;
		p->next = g->adjList[i].firstedge;
		g->adjList[i].firstedge = p;
		/*将编号为j的结点添加到邻接表中，有向图不用添加该结点，去掉下面if语句*/
		if (flag == 0)
		{
			p = (EdgeNode*)malloc(sizeof(EdgeNode));
			p->adjvex = i; /*邻接点序号为i*/
			p->next = g->adjList[j].firstedge; /*将新边表结点p插到顶点vi边表头部*/
			g->adjList[j].firstedge = p;
		}
	}
}


void DispGraph(GraphAdjList* G)
{
	int i, j;
	for (i = 0; i < G->numVertexes; i++)
	{
		printf("%d->", i);
		while (1)
		{
			if (G->adjList[i].firstedge == NULL)
			{
				printf("^");
				break;
			}
			printf("%d->", G->adjList[i].firstedge->adjvex);
			G->adjList[i].firstedge = G->adjList[i].firstedge->next;
		}
		printf("\n");

	}
}


void DFS(GraphAdjList* G, int v)
{
	EdgeNode* p;
	if (v < 0 || v >= G->numVertexes)
		return;
	else
	{
		visited[v] = 1;     //已经访问标记
		printf("%c ", G->adjList[v].data);
		p = G->adjList[v].firstedge;   //p指向顶点v的第一条边
		while (p != NULL)
		{
			if (visited[p->adjvex] != 1)
				DFS(G, p->adjvex);
			p = p->next;
		}
	}
}
void DFSTravel(GraphAdjList* G)
{
	int v;
	printf("深度优先遍历顺序为：");
	for (v = 0; v < G->numVertexes; v++)
		visited[v] = 0;
	for (v = 0; v < G->numVertexes; v++)
	{
		if (!visited[v])
			DFS(G, v);
	}
}

int visitBFS[MaxVex];
void BFS(GraphAdjList* G, int v)
{
	EdgeNode* p;
	int que[MaxVex], front = 0, rear = 0;   //队列定义的简单写法
	int j;
	printf("%c ", G->adjList[v].data);
	visitBFS[v] = 1;
	rear = (rear + 1) % MaxVex;     //当前顶点v进入队列
	que[rear] = v;
	while (front != rear)     //队空时遍历完成
	{
		front = (front + 1) % MaxVex;     //顶点出队
		j = que[front];
		p = G->adjList[j].firstedge;    //p指向出队顶点j的第一条边
		while (p != NULL)
		{
			if (visitBFS[p->adjvex] == 0)
			{
				printf("%c", p->adjvex);
				visitBFS[p->adjvex] = 1;
				rear = (rear + 1) % MaxVex;   //该顶点进队
				que[rear] = p->adjvex;
			}
			p = p->next;
		}
	}
}

void BFSTravel(GraphAdjList* G)
{
	int i;
	printf("\n广度优先遍历顺序为：");
	for (i = 0; i < G->numVertexes; i++)
	{
		if (visitBFS[i] == 0)
			BFS(G, i);
	}
}

void MenuGraph() /*显示菜单子函数*/
{
	printf("\n 图子系统");
	printf("\n =================================================");
	printf("\n| 1——更新邻接表 |");
	printf("\n| 2——深度优先遍历 |");
	printf("\n| 3——广度优先遍历 |");
	printf("\n| 0——返回 |");
	printf("\n =================================================");
	printf("\n请输入菜单号（0-3）:");
}

void graph()
{
	int i, f;
	char ch1, ch2, a;
	GraphAdjList g;
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y')
	{
		MenuGraph();
		scanf("%c", &ch2);
		getchar();
		switch (ch2)
		{
		case '1':
			printf("要建立的是有向图（1）还是无向图（0），请选择（输入1或0）：");
			scanf("%d", &f);
			CreateAGraph(&g, f);
			DispGraph(&g);
			break;
		case '2':
			DFSTravel(&g);
			break;
		case '3':
			BFSTravel(&g);
			break;
		case '0':
			ch1 = 'n'; break;
		default:
			printf("输入有误，请输入0-3进行选择！");
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

