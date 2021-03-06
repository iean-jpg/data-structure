#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MAX_STR_LEN 40
#define ERROR 0
#define OK 1
#define TRUE 1
#define FALSE 0
#define MAX_STR_LEN 40  
typedef char SString[MAX_STR_LEN + 1];
typedef int Status;

Status StrAssign(SString T, char* chars)
{  
	int i;
	if (strlen(chars) > MAX_STR_LEN)
		return ERROR;
	else
	{
		T[0] = strlen(chars);
		for (i = 1; i <= T[0]; i++)
			T[i] = *(chars + i - 1);
		return OK;
	}
}

void StrCopy(SString T, SString S)
{ 
	int i;
	for (i = 0; i <= S[0]; i++)
		T[i] = S[i];
}

Status StrEmpty(SString S)
{  
	if (S[0] == 0)
		return TRUE;
	else
		return FALSE;
}

int StrCompare(SString S, SString T)
{  
	int i;
	for (i = 1; i <= S[0] && i <= T[0]; ++i)
		if (S[i] != T[i])
			return S[i] - T[i];
	return S[0] - T[0];
}

int StrLength(SString S)
{ 
	return S[0];
}

void ClearString(SString S)
{ 
	S[0] = 0;
}

Status Concat(SString T, SString S1, SString S2) 
{  
	int i;
	if (S1[0] + S2[0] <= MAX_STR_LEN)
	{ 
		for (i = 1; i <= S1[0]; i++)
			T[i] = S1[i];
		for (i = 1; i <= S2[0]; i++)
			T[S1[0] + i] = S2[i];
		T[0] = S1[0] + S2[0];
		return TRUE;
	}
	else
	{  
		for (i = 1; i <= S1[0]; i++)
			T[i] = S1[i];
		for (i = 1; i <= MAX_STR_LEN - S1[0]; i++)
			T[S1[0] + i] = S2[i];
		T[0] = MAX_STR_LEN;
		return FALSE;
	}
}

Status SubString(SString Sub, SString S, int pos, int len)
{ 
	int i;
	if (pos<1 || pos>S[0] || len<0 || len>S[0] - pos + 1)
		return ERROR;
	for (i = 1; i <= len; i++)
		Sub[i] = S[pos + i - 1];
	Sub[0] = len;
	return OK;
}

int Index(SString S, SString T,int pos)
{ 
	int i, j;
	if (1 <= pos && pos <= S[0])
	{
		i = pos;
		j = 1;
		while (i <= S[0] && j <= T[0])
			if (S[i] == T[j])   
			{
				++i;
				++j;
			}
			else   
			{
				i = i - j + 2;
				j = 1;
			}
		if (j > T[0])
			return i - T[0];
		else
			return 0;
	}
	else
		return 0;
}

Status StrInsert(SString S, int pos, SString T)
{
	int i;
	if (pos<1 || pos>S[0] + 1)
		return ERROR;
	if (S[0] + T[0] <= MAX_STR_LEN)
	{ 
		for (i = S[0]; i >= pos; i--)
			S[i + T[0]] = S[i];
		for (i = pos; i < pos + T[0]; i++)
			S[i] = T[i - pos + 1];
		S[0] += T[0];
		return TRUE;
	}
	else
	{ 
		for (i = MAX_STR_LEN; i >= pos + T[0]; i--)
			S[i] = S[i - T[0]];
		for (i = pos; i < pos + T[0] && i <= MAX_STR_LEN; i++)
			S[i] = T[i - pos + 1];
		S[0] = MAX_STR_LEN;
		return FALSE;
	}
}

Status StrDelete(SString S, int pos, int len)
{ 
	int i;
	if (pos<1 || pos>S[0] - len + 1 || len < 0)
		return ERROR;
	for (i = pos + len; i <= S[0]; i++)
		S[i - len] = S[i];
	S[0] -= len;
	return OK;
}

Status Replace(SString S, SString T, SString V) 
{  
	
	int i = 1; 
	Status k;
	if (StrEmpty(T))  
		return ERROR;
	i = Index(S, T, i);   
	if (i!=0) 
	{
		StrDelete(S, i, StrLength(T));  
		k = StrInsert(S, i, V);
		if (k==0) 
			return ERROR;
	}
	return OK;
}

void StrPrint(SString T)
{  
	int i;
	for (i = 1; i <= T[0]; i++)
		printf("%c", T[i]);
	printf("\n");
}


void MenuString()
{
    printf("\n 串子系统");
    printf("\n =================================================");
    printf("\n| 1建立新串 |");
    printf("\n| 2求子串|");
    printf("\n| 3插入子串 |");
    printf("\n| 4删除子串 |");
    printf("\n| 5查找子串 |");
    printf("\n| 6比较子串 |");
    printf("\n| 7连接两串 |");
    printf("\n| 8子串替换 |");
    printf("\n| 0返回 |");
    printf("\n =================================================");
    printf("\n请输入菜单号（0-8）:");
}

void string()
{
    char Astr[100] = { 0 };
    char Bstr[100] = { 0 };
    char ch1, ch2, a;
	SString s, t, r, i,g;
	int x, y, flag;
    ch1 = 'y';
    while (ch1 == 'y' || ch1 == 'Y')
    {
        MenuString();
        scanf("%c", &ch2);
        getchar();
        switch (ch2)
        {
        case'1':
            printf("请输入字符串：");
            scanf("%s", Astr);
            StrAssign(s, Astr);
            printf("建立的字符串为：\n");
            StrPrint(s);
            break;
        case'2':
			printf("输入要找的子串的起始位置：");
			scanf("%d", &x);
			printf("输入要查找子串的长度：");
			scanf("%d",&y);
            SubString(r,s,x,y);
            printf("查找的子串为：\n");
            StrPrint(r);
            break;
        case'3':
            printf("请输入要插入的位置：");
            scanf("%d", &x);
            printf("输入要插入的子串:");
            scanf("%s", Astr);
            StrAssign(t, Astr);
            StrInsert(s, x, t);
            printf("插入子串后为：\n");
            StrPrint(s);
            break;
        case'4':
            printf("删除子串的起始位置：");
            scanf("%d", &x);
            printf("删除子串的长度：");
            scanf("%d", &y);
            StrDelete(s, x, y);
            printf("删除子串后的串为：\n");
            StrPrint(s);
            break;
        case'5':
            printf("输入要查找的子串:");
            scanf("%s", Astr);
            StrAssign(t, Astr);
            flag=Index(s, t, 1);
			if (flag != 0)
				printf("该子串存在");
			else
				printf("子串不存在");
            break;
        case'6':
            printf("输入要比较的串A：");
            scanf("%s", Astr);
            printf("输入要比较的串B:");
            scanf("%s", Bstr);
            StrAssign(t, Astr);
            StrAssign(r, Bstr);
            if (StrCompare(t, r) > 0)
                printf("A串更大");
            else if (StrCompare(t, r) < 0)
                printf("B串更大");
            else
                printf("两串相等");
            break;
        case'7':
            printf("输入串A：");
            scanf("%s", Astr);
            printf("输入串B：");
            scanf("%s", Bstr);
            StrAssign(t, Astr);
            StrAssign(i, Bstr);
            Concat(g,t,i);
            printf("连接后的串为：\n");
            StrPrint(s);
            break;
        case'8':
            printf("输入要替换的串：");
            scanf("%s", Astr);
			printf("输入要被替换的串:");
			scanf("%s", Bstr);
            StrAssign(t, Astr);
			StrAssign(r, Bstr);
			Replace(s,r,t);
            printf("替换后的串为：\n");
            StrPrint(s);
			break;
        case '0':
            ch1 = 'n'; break;
        default:
            printf("输入有误，请输入（0-8）范围内的数");
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
