#include"LinkLsit.h"
#include"LinkStack.h"
#include"LinkQueue.h"
#include"string.h"
#include"BiTree.h"
#include"Graph.h"
#include"search.h"
#include"sort.h"

int main()
{
	int choice;
	char ch;
	ch = 'y';
	while (ch == 'y' || ch == 'Y')
	{
		printf("\n");
		printf("\n			数据结构实验系统主菜单");
		printf("\n=======================================================================================");
		printf("\n				1-线性表					   |");
		printf("\n				2— 栈					           |");
		printf("\n				3—队 列					           |");
		printf("\n				4—  串					           |");
		printf("\n				5—二叉树					   |");
		printf("\n				6—  图					           |");
		printf("\n				7—查 找					           |");
		printf("\n				8—排 序					           |");
		printf("\n				0—退 出					           |");
		printf("\n======================================================================================");
		printf("\n请选择菜单号(0-8):");
		scanf("%d", &choice);
		getchar();
		switch (choice)
		{
		case 1:linklist(); break;
		case 2:linkstack(); break;
		case 3:linkqueue(); break;
		case 4:string(); break;
		case 5:btree(); break;
		case 6:graph(); break;
		case 7:search(); break;
		case 8:sort(); break;
		case 0:ch = 'n'; break;
		default:printf("菜单选择错误，请重新选择!");
		}
	}
	return 0;
}