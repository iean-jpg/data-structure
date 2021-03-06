#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define false 0
#define true 1
typedef int Keytype;
typedef struct
{
	Keytype key;
}Searchl;

//顺序查找
int Sequential_Search(Searchl r[], int n, int key)
{
	int i;
	r[0].key = key;
	i = n;
	while (r[i].key != key)
	{
		i--;
	}
	return i;
}

//折半查找
int Binary_Search(Searchl r[], int n, int key)
{
	int low, high, mid;
	low = 1;
	high = n;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (key < r[mid].key)
			high = mid - 1;
		else if (key > r[mid].key)
			low = mid + 1;
		else
			return mid;
	}
	return 0;
}

typedef struct /*分块查找的索引表类型*/
{
	Keytype key; /*关键字*/
	int low, high; /*每块的低、高地址*/
}IdxType;


int find_max(Searchl a[], int s, int e)
{
	int max = a[s].key;
	for (int i = s + 1; i <= e; i++)
	{
		if (a[i].key > max)
			max = a[i].key;
	}
	return max;
}

void CreatIdx(Searchl r[], IdxType idx[], int m, int n)
{ /*分块查找的建立索引表算法函数*/
	int i, ci=0;
	int k = m / n;
	int l = m % n;
	if (l >= 5)k += 1;
	for (i = 0; i < m; i+=n,ci++)
	{
		idx[ci].low = i;
		idx[ci].high = i+(n-1);
		idx[ci].key = find_max(r, i, i + (n - 1));
	}
}

int BlkSearch(Searchl r[], IdxType idx[], int m, Keytype k)
{ /*分块查找算法函数*/
	int low = 0, high = m - 1, mid, i, count1 = 0, count2 = 0;
	int b = m;

	while (low <= high)
	{
		mid = (low + high) / 2;
		if (idx[mid].key >= k)
			high = mid - 1;
		else
			low = mid + 1;
		count1++;
	}
	if (low < m)
	{
		
		i = idx[low].low;

		while (i <= idx[low].low + b - 1 && r[i].key != k)
		{
			i++; count2++;
			printf("%d ", r[i].key);
		}
		printf("\n");

		if (i <= idx[low].low + b - 1)
			return i;
		else
			return -1;
	}
	return -1;
}

typedef struct treenode /*二叉排序树的结点类型*/
{
	Keytype key; /*关键字*/
	struct treenode* lchild, * rchild; /*左、右孩子指针*/
}BTNode,*BTree;

int SearchBST(BTree T, Keytype key, BTree f, BTree* p) {
	//如果 T 指针为空，说明查找失败，令 p 指针指向查找过程中最后一个叶子结点，并返回查找失败的信息
	if (!T) {
		*p = f;
		return false;
	}
	//如果相等，令 p 指针指向该关键字，并返回查找成功信息
	else if (key == T->key) {
		*p = T;
		return true;
	}
	//如果 key 值比 T 根结点的值小，则查找其左子树；反之，查找其右子树
	else if (key < T->key) {
		return SearchBST(T->lchild, key, T, p);
	}
	else {
		return SearchBST(T->rchild, key, T, p);
	}
}

int num = 1;
void DispBStree(BTree bt)
{ /*用广义表显示二叉排序树函数*/
	if (bt)
	{
		printf("%d", bt->key);
		if (bt->lchild || bt->rchild)
		{
			printf("("); num++;
		}
		DispBStree(bt->lchild);
		if (bt->rchild)
			if (bt->lchild || bt->rchild)
				printf(",");
		DispBStree(bt->rchild);
	}
}
//删除函数
int Delete(BTree* p)
{
	BTree q, s;
	//情况 1，结点 p 本身为叶子结点，直接删除即可
	if (!(*p)->lchild && !(*p)->rchild) {
		*p = NULL;
	}
	else if (!(*p)->lchild) { //左子树为空，只需用结点 p 的右子树根结点代替结点 p 即可；
		q = *p;
		*p = (*p)->rchild;
		free(q);
	}
	else if (!(*p)->rchild) {//右子树为空，只需用结点 p 的左子树根结点代替结点 p 即可；
		q = *p;
		*p = (*p)->lchild;//这里不是指针 *p 指向左子树，而是将左子树存储的结点的地址赋值给指针变量 p
		free(q);
	}
	else {//左右子树均不为空，采用第 2 种方式
		q = *p;
		s = (*p)->lchild;
		//遍历，找到结点 p 的直接前驱
		while (s->rchild)
		{
			q = s;
			s = s->rchild;
		}
		//直接改变结点 p 的值
		(*p)->key = s->key;
		//判断结点 p 的左子树 s 是否有右子树，分为两种情况讨论
		if (q != *p) {
			q->rchild = s->lchild;//若有，则在删除直接前驱结点的同时，令前驱的左孩子结点改为 q 指向结点的孩子结点
		}
		else {
			q->lchild = s->lchild;//否则，直接将左子树上移即可
		}
		free(s);
	}
	return true;
}

int BSTDelete(BTree* bt, Keytype k)
{ /*在二叉排序树t中删除关键字为k的节点函数*/
	if (!(*bt)) {//不存在关键字等于key的数据元素
		return false;
	}
	else
	{
		if (k == (*bt)->key) {
			Delete(bt);
			return true;
		}
		else if (k < (*bt)->key) {
			//使用递归的方式
			return BSTDelete(&(*bt)->lchild, k);
		}
		else {
			return BSTDelete(&(*bt)->rchild, k);
		}
	}
}

int BSTInsert(BTree* bt, Keytype k)
{ //二叉树插入操做
	BTree p = NULL;
	//如果查找不成功，需做插入操作
	if (!SearchBST((*bt), k, NULL, &p)) {
		//初始化插入结点
		BTree s = (BTree)malloc(sizeof(BTNode));
		s->key = k;
		s->lchild = s->rchild = NULL;
		//如果 p 为NULL，说明该二叉排序树为空树，此时插入的结点为整棵树的根结点
		if (!p) {
			*bt = s;
		}
		//如果 p 不为 NULL，则 p 指向的为查找失败的最后一个叶子结点，只需要通过比较 p 和 e 的值确定 s 到底是 p 的左孩子还是右孩子
		else if (k < p->key) {
			p->lchild = s;
		}
		else {
			p->rchild = s;
		}
		return true;
	}
	//如果查找成功，不需要做插入操作，插入失败
	return false;
}

BTree CreateBST(Keytype str[], int n)
{ /*建立二叉排序树函数*/
	BTree T = NULL;
	for (int i = 0; i < 5; i++) {
		BSTInsert(&T, str[i]);
	}
	return T;
}

BTree BSTSearch(BTree bt, Keytype k)
{ /*二叉排序树的元素查找函数*/

		//如果递归过程中 bt 为空，则查找结果，返回NULL；或者查找成功，返回指向该关键字的指针
		if (!bt || k == bt->key) {
			return bt;
		}
		else if (k < bt->key) {
			//递归遍历其左孩子
			return BSTSearch(bt->lchild, k);
		}
		else {
			//递归遍历其右孩子
			return BSTSearch(bt->rchild, k);
		}
}

void MenuBTree()
{ /*显示二叉排序树子菜单函数*/
	printf("\n 二叉排序树 ");
	printf("\n==================================================");
	printf("\n| 1------建立二叉排序树 |");
	printf("\n| 2------插入一个元素 |");
	printf("\n| 3------删除一个元素 |");
	printf("\n| 4------查找一个元素 |");
	printf("\n| 0------返回 |");
	printf("\n==================================================");
	printf("\n请输入序号（0-4）选择要进行的操作:");
}

void BTFun()
{ /*二叉排序树子函数*/
	Keytype str[100];
	BTree bt=NULL;
	int i, n, x, menux;
	MenuBTree();
	scanf("%d", &menux);
	do {
		switch (menux) /*判断进行何种操作*/
		{
		case 1: /*建立二叉排序树*/
			printf("请输入要生成二叉排序树的关键字的个数:");
			scanf("%d", &n);
			printf("请输入二叉排序树的各个关键字:");
			for (i = 0; i<n;i++) scanf("%d", &str[i]);
				bt = CreateBST(str, n);
				printf("建立的二叉排序树广义表表示法为:");
				DispBStree(bt);
				break;
		case 2: /*在二叉排序树中插入一个元素*/
			printf("请输入要插入的元素值: ");
				scanf("%d", &x);
				BSTInsert(&bt, x);
				printf("插入后的二叉排序树为: ");
				DispBStree(bt);
				break;
		case 3: /*在二叉排序树中删除一个元素*/
			printf("请输入要删除的元素:");
			scanf("%d", &x);
			BSTDelete(&bt, x);
			printf("删除元素%d后的二叉排序树为:", x);
			DispBStree(bt);
			break;
		case 4: /*在二叉排序树中查找某元素*/
			printf("请输入查找的元素值:");
			scanf("%d", &x);
			if ((BSTSearch(bt, x)) != NULL)
				printf("在二叉排序树中存在元素%d！", x);
			else
				printf("在二叉排序树中不存在元素%d！", x);
			break;
		case 0:
			return;
			break;
		default:
			printf("输入选项错误,请重新输入(0-4)!");
		}
		MenuBTree();
		scanf("%d", &menux);
	} while (1);
}

void Menu()
{ /*显示菜单子函数*/
	printf("\n 查找子系统");
	printf("\n==================================================");
	printf("\n| 1——顺序查找 |");
	printf("\n| 2——折半查找 |");
	printf("\n| 3——分块查找 |");
	printf("\n| 4——二叉树排序树查找 |");
	printf("\n| 0——返回 |");
	printf("\n==================================================");
	printf("\n请输入菜单号（0-4）:");
}

void search()
{
	Searchl r[MAXSIZE];
	IdxType idx[MAXSIZE];
	int i, m, n, x, k, address;
	char ch1, ch2, a;
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y')
	{
		Menu();
		scanf("%c", &ch2);
		getchar();
		switch (ch2)
		{
		case '1':
			printf("请输入表的元素个数(0-%d):", MAXSIZE - 1);
			scanf("%d", &n);
			printf("请输入%d个表中的关键字(整数):", n);
			for (i = 1; i <= n; i++)
				scanf("%d", &r[i].key);
			printf("请输入要查找的关键字:");
			scanf("%d", &x);
			if ((address = Sequential_Search(r, n, x)) != 0)
				printf("该元素在表中的位置为:%d", address);
			else
				printf("该元素不在表中!");
			break;
		case '2':
			printf("请输入表的元素个数(0-%d):", MAXSIZE - 1);
			scanf("%d", &n);
			printf("请按照从小到大的顺序输入%d个关键字(为整数):", n);
			for (i = 1; i <= n; i++)
				scanf("%d", &r[i].key);
			printf("请输入要查找的关键字:");
			scanf("%d", &x);
			if ((address = Binary_Search(r, n, x)) != 0)
				printf("该元素在表中的位置为:%d", address);
			else
				printf("该元素不在该有序表中!");
			break;
		case '3':
			int q;
			printf("请输入表的元素个数(0-%d):", MAXSIZE - 1);
			scanf("%d", &m);
			printf("请输入表中的关键字(为整数)，要求块内无序，块间有序:\n");
			for (i = 0; i<m;i++) scanf("%d", &r[i].key);
				printf("表输入索引表每块的大小：");
				scanf("%d", &n);
				CreatIdx(r, idx, m, n);
				printf("\n建立的顺序表为:\n");
				for (i = 0; i<m;i++) printf("%6d", r[i].key);
					printf("\n索引表信息如下:");
					printf("\n低地址\t高地址\t最大关键字\n");
					if (m % n == 0)
					{
						q = m / n;
						for (i = 0; i < q; i++) printf("%5d\t%5d\t%5d\n", idx[i].low, idx[i].high, idx[i].key);
						printf("请输入要查找的元素的关键字:");
						scanf("%d", &k);
						if ((address = BlkSearch(r, idx, q, k)) != -1)
							printf("该元素在表中的位置为:%d", address + 1);
						else
							printf("该元素不在表中!");
					}
					else
					{
						q = (m / n) + 1;
						for (i = 0; i < q; i++) printf("%5d\t%5d\t%5d\n", idx[i].low, idx[i].high, idx[i].key);
						printf("请输入要查找的元素的关键字:");
						scanf("%d", &k);
						if ((address = BlkSearch(r, idx, q, k)) != -1)
							printf("该元素在表中的位置为:%d", address + 1);
						else
							printf("该元素不在表中!");
					}
								break;
		case '4':
			BTFun();
				break;
		case '0':
			ch1 = 'n';
			break;
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