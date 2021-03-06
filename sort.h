#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100

typedef int KeyType;
typedef struct
{
	KeyType Key;
}LineList;


//直接插入排序
void InsertSort(LineList r[], int n)
{
	int i, j, k;
	for (i = 0; i <= n; i++)
	{
		for (j = i - 1; j >= 0; j--)
			if (r[j].Key < r[i].Key)
				break;
		if (j != i - 1)
		{
			int temp = r[i].Key;
			for (k = i - 1; k > j; k--)
				r[k + 1].Key = r[k].Key;
			r[k + 1].Key = temp;
		}
	}	
}

//希尔排序
void ShellSort(LineList r[],int n)
{ 
	int i, j, temp, gap;
	for (gap = n / 2; gap >= 1; gap /= 2)
	{
		for (i = 0 + gap; i < n; i += gap)
		{
			temp = r[i].Key;
			j = i - gap;
			while (j >= 0 && r[j].Key > temp)
			{
				r[j + gap].Key = r[j].Key;
				j -= gap;
			}
			r[j + gap].Key = temp;
		}
	}
}

//冒泡排序
void BubbleSort(LineList r[], int n)
{
	int i, j, temp;
	for (i = 0; i <= n; i++)
	{
		for (j = 0; j <= n-i-1	; j++)
		{
			if (r[j].Key > r[j + 1].Key)
			{
				temp = r[j].Key;
				r[j].Key = r[j + 1].Key;
				r[j + 1].Key = temp;
			}
		}
	}

}

//快速排序
void QuickSort(LineList r[], int low,int high)
{
	int first = low;
	int last = high;
	int key = r[first].Key;
	if (low >= high)
		return;
	while (first < last)
	{
		while (first<last && r[last].Key>key)
		{
			last--;
		}
		r[first].Key = r[last].Key;
		while (first < last && r[first].Key < key)
		{
			first++;
		}
		r[last].Key = r[first].Key;
	}
	r[first].Key = key;
	QuickSort(r, low, first - 1);
	QuickSort(r, first + 1, high);
}

//直接选择排序
void SelectSort(LineList r[], int n)
{
	int i, j, k, index;    
	for (i = 0; i <= n - 1; i++)   
	{
		k = i;
		for (j = i + 1; j <= n; j++)    
		{
			if (r[j].Key < r[k].Key)   
				k = j;      
		}
		if (k != j)    
		{
			index = r[i].Key;   
			r[i].Key = r[k].Key;    
			r[k].Key = index;
		}
	}
}

/*堆排序的筛选函数*/
void Sift(LineList r[], int low, int high)
{ 
	int rc, j;
	rc = r[low].Key;
	for (j = 2 * low; j <= high; j = j * 2)
	{
		if (j < high && r[j].Key < r[j + 1].Key)j++;
		if (rc > r[j].Key)break;
		r[low].Key = r[j].Key;
		low = j;
	}
	r[low].Key = rc;
}

/*建堆函数*/
void HeapSort(LineList r[], int n)
{ 
	int temp, i, j;
	for (i = n / 2; i > 0; i--)//通过循环初始化顶堆
	{
		Sift(r, i, n);
	}
	for (i = n; i > 0; i--)
	{
		temp = r[1].Key;
		r[1].Key = r[i].Key;
		r[i].Key = temp;//将堆顶记录与未排序的最后一个记录交换
		Sift(r, 1, i - 1);//重新调整为顶堆
	}

}

void Merge(int* num, int start, int mid, int end)
{
	int* temp = (int*)malloc((end - start + 1) * sizeof(int));
	int i = start;
	int j = mid + 1;
	int k = 0;

	while (i <= mid && j <= end)
	{
		if (num[i] <= num[j])
		{
			temp[k++] = num[i++];
		}
		else
		{
			temp[k++] = num[j++];
		}
	}

	while (i <= mid)
	{
		temp[k++] = num[i++];
	}
	while (j <= end)
	{
		temp[k++] = num[j++];
	}

	//将临时区域中排序后的元素，整合到原数组中
	for (i = 0; i < k; i++)
	{
		num[start + i] = temp[i];
	}

	free(temp);
}

void MergeSort(int* num, int start, int end)
{
	int mid = start + (end - start) / 2;

	if (start >= end)
	{
		return;
	}

	MergeSort(num, start, mid);
	MergeSort(num, mid + 1, end);

	Merge(num, start, mid, end);
}

void OutList(LineList r[], int n)
{
	int i;
	printf("排序后的记录为：");
	for (i = 1; i <= n; i++)
		printf("%5d", r[i].Key);
}

void MenuSort()
{ /*显示菜单子函数*/
	printf("\n 排序子系统");
	printf("\n==================================================");
	printf("\n| 1——更新排序数据 |");
	printf("\n| 2——直接插入排序 |");
	printf("\n| 3——希尔排序 |");
	printf("\n| 4——冒泡排序 |");
	printf("\n| 5——快速排序 |");
	printf("\n| 6——直接选择排序 |");
	printf("\n| 7——堆排序 |");
	printf("\n| 8——归并排序 |");
	printf("\n| 0——返回 |");
	printf("\n==================================================");
	printf("\n请输入菜单号（0-8）:");
}

void sort()
{
	int i, n=0;
	int arr[MAXSIZE];
	LineList r[MAXSIZE];
	char ch1, ch2, a;
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y')
	{
		MenuSort();
		scanf("%c", &ch2);
		getchar();
		switch (ch2)
		{
		case '1':
			printf("请输入待排序表的长度：");
			scanf("%d", &n);
			printf("请输入%d个整数：", n);
			for (i = 1; i <= n; i++)
				scanf("%d", &r[i].Key);
			OutList(r, n);
			break;
		case '2':
			InsertSort(r, n);
			printf("进行直接插入排序，");
			OutList(r, n);
			break;
		case '3':
			ShellSort(r, n);
			printf("进行希尔插入排序，");
			OutList(r, n);
			break;
		case '4':
			BubbleSort(r, n);
			printf("进行冒泡排序，");
			OutList(r, n);
			break;
		case '5':
			QuickSort(r, 1, n);
			printf("进行快速排序，");
			OutList(r, n);
			break;
		case '6':
			SelectSort(r, n);
			printf("进行直接选择排序，");
			OutList(r, n);
			break;
		case '7':
			HeapSort(r, n);
			printf("进行堆排序，");
			OutList(r, n);
			break;
		case '8':
			printf("输入待排序表的长度：");
			scanf("%d", &n);
			printf("请输入%d个整数：", n);
			for (i = 0; i < n; i++)
				scanf("%d", &arr[i]);
			MergeSort(arr, 0, n-1);
			printf("进行归并排序，");
			for (i = 0; i < n; i++)
			{
				printf("%5d ", arr[i]);
			}
			printf("\n");
			break;
		case '0':
			ch1 = 'n';
			break;
		default:
			printf("输入有误，请输入0-8进行选择！");
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