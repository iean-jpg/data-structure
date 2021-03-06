#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define MAX 25

typedef int DataType, Status;
typedef struct StackNode {
	DataType data;
	struct StackNode* next;
}StackNode,*LinkStack;

Status InitStack(LinkStack &S)
{
	S = (LinkStack)malloc(sizeof(StackNode));
	S->next = NULL;
	return OK;
}

int isEmpty(LinkStack& lst)
{
	return lst->next == NULL;
}

LinkStack push(LinkStack& S, DataType e)
{
	LinkStack L = (LinkStack)malloc(sizeof(StackNode));
	L->data = e;	
	L->next = S->next;
	S->next = L;
	return S;
}

Status pop(LinkStack& S,DataType& e)
{
	if (S->next == NULL)return 0;
	LinkStack p = S->next;
	S->next = p->next;
	e = p->data;
	free(p);
	return 1;
}

int getTop(LinkStack S, DataType& e)
{
	LinkStack p = S;
	if (p->next == NULL)return ERROR;
	else {
		while (p->next != NULL) {
			p = p->next;
		}
		e = p->data;
		return OK;
	}
}

void ShowStack(LinkStack& s)
{
	LinkStack p = s->next;
	while (p != NULL) {
		printf("%d\t", p->data);
		p = p->next;
	}
	printf("\n");
}

void conversion(int n)
{
	DataType e;
	LinkStack S;
	InitStack(S);
	while (n)
	{
		push(S, n % 2);
		n = n / 2;
	}
	while (!isEmpty(S))
	{
		pop(S, e);
		printf("%d", e);
	}
} 




typedef struct Stack {
	ElemType* base;
	ElemType* top;
	int stacksize;
}SqStack;

int CreateStack(SqStack* S) {
	S->base = (ElemType*)malloc(sizeof(SqStack) * 10);
	if (!S->base) exit(-1);
	S->top = S->base;
	S->stacksize = 10;
	return 1;
}
 
ElemType GetTop(SqStack* S) {
	if (S->top == S->base)
		return 0;
	return *(S->top - 1);
}

int Push(SqStack* S, ElemType e) {
	if ((S->top - S->base) >= S->stacksize) {
		S->base = (ElemType*)realloc(S->base, (S->stacksize + 5) * sizeof(SqStack));
		if (!S->base)
			exit(-1);
		S->top = S->base + S->stacksize;
		S->stacksize += 5;
	}
	*S->top = e;
	S->top++;
	return 1;
}

int Pop(SqStack* S, ElemType* e) {
	if (S->top == S->base)
		return 0;
	*e = *(--S->top);
	return 1;
}


void DestoryStack(SqStack* S) {
	free(S->base);
	S->base = NULL;
	S->top = NULL;
	S->stacksize = 0;

}


ElemType Theta(int l, char m, int r) {
	switch (m) {
	case'+': return l + r;
	case'-': return 1 - r;
	case'*': return l * r;
	case'/': return l / r;
	}
}


int Is_Pop(char x, char y) {
	if (x == '(')
		return 0;
	if (y == '(' && x != ')')
		return 0;
	if (y == '*' || y == '/') {
		if (x == '+' || x == '-')
			return 0;
	}
	return 1;
}


int In_Op(char a) {
	switch (a) {
	case '+': return 1;
	case '-': return 1;
	case '*': return 1;
	case '/': return 1;
	case '(': return 1;
	case ')': return 1;
	case '#': return 1;
	default:return 0;
	}
}

char* TransmitExpression(char* a) {
	int i, j = 0;
	char b[20] = { 0 };
	char* result = NULL;
	SqStack OPTR;
	ElemType e;
	CreateStack(&OPTR);
	Push(&OPTR, '#');
	for (i = 0; a[i]; i++) {
		if (!In_Op(a[i])) {
			b[j++] = a[i]; 
		}
		else {
			if (GetTop(&OPTR) == '#') {
				Push(&OPTR, a[i]);	
				continue;
			}
			if (Is_Pop(GetTop(&OPTR), a[i])) {  
				if (a[i] == ')') {	
					while (GetTop(&OPTR) != '(') {
						Pop(&OPTR, &e);	 
						b[j++] = (char)e;
					}
					Pop(&OPTR, &e); 
				}
				else { 			 
					while (GetTop(&OPTR) != '#') { 
						Pop(&OPTR, &e);
						b[j++] = (char)e;
					}
					Push(&OPTR, a[i]);
				}
			}
			else {
				Push(&OPTR, a[i]); 
								
			}
		}
	}

	while (GetTop(&OPTR) != '#') {
		Pop(&OPTR, &e);
		b[j++] = (char)e;
	}

	result = (char*)malloc(sizeof(char) * 20);
	strcpy(result, b);

	DestoryStack(&OPTR);
	return result;
}
 
ElemType EvaluateExpression(char* a) {
	int i;
	ElemType l = 0, r = 0, e = 0, ret = 0;

	SqStack OPND;
	CreateStack(&OPND);
	for (i = 0; a[i]; i++) {
		if (!In_Op(a[i])) {
			Push(&OPND, (ElemType)(a[i] - 48));
		}
		else {
			Pop(&OPND, &r);
			Pop(&OPND, &l);
			Push(&OPND, Theta(l, a[i], r));
		}
	}
	ret = GetTop(&OPND);
	DestoryStack(&OPND);
	return ret;
}



void MenuStack()
{ /*显示菜单子函数*/
	printf("\n 栈子系统");
	printf("\n =================================================");
	printf("\n| 1——初始化栈 |");
	printf("\n| 2——入栈操作 |");
	printf("\n| 3——出栈操作 |");
	printf("\n| 4——求栈顶元素 |");
	printf("\n| 5——显示栈中元素 |");
	printf("\n| 6——十、二进制数转换 |");
	printf("\n| 7——表达式转换并求值 |");
	printf("\n| 0——返回 |");
	printf("\n =================================================");
	printf("\n请输入菜单号（0-7）:");
}

void linkstack()
{
	int i, n, flag;
	LinkStack S=NULL;
	DataType x;
	char ch1, ch2, a;
	char exp[100], *postexp; 
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y')
	{
		MenuStack();
		scanf("%c", &ch2);
		getchar();
		switch (ch2)
		{
		case'1':
			InitStack(S);
			printf("栈的初始化完成！");
			break;
		case'2':
			printf("请输入要入栈的元素个数：");
			scanf("%d", &n);
			printf("请输入%d个整数进行入栈：", n);
			for (i = 0; i < n; i++)
			{
				scanf("%d", &x);
				push(S, x);
			}
			printf("入栈成功！");
			break;
		case'3':
			printf("请输入要出栈的元素个数：");
			scanf("%d", &n);
			printf("出栈的元素为：");
			for (i = 0; i < n; i++) {
				pop(S, x);
				printf("%5d", x);
			}
			break;
		case '4':
			if (flag = getTop(S, x))
				printf("当前的栈顶元素值为：%d", x);
			break;
		case '5':
			ShowStack(S);
			break;
		case'6':
			printf("请输入十进制正整数为:");
			scanf("%d", &x);
			conversion(x);
			break;
		case'7':
			printf("请输入一个算术表达式（只有+、-、*、/四种运算符），以'#'结束：");
			scanf("%s", &exp);
			printf("则该表达式的中缀表达式为：%s\n", exp);
			postexp = TransmitExpression(exp);
			printf("转换之后的后缀表达式为（每个操作数用“#”分隔）：%s\n", TransmitExpression(exp));
			printf("表达式的值为:%d\n", EvaluateExpression(postexp));
			break;
		case '0':
			ch1 = 'n'; break;
		default:
			printf("输入有误，请输入0-7进行选择！");
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