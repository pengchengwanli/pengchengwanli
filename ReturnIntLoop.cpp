//返回一个整数数组中最大子数组的和（数组首尾相连）
#include<iostream>
#define N 100
using namespace std;

//构造子数组结构
typedef struct SArray
{
	int Sdata;	//子数组中的数
	int start;	//子数组的起始位置
	int end;	//子数组的终止位置
}SArray;

//构造链表的存储结构
typedef struct LNode
{
	int data;	//数
	int position;	//数所在数组中的位置
	struct LNode *next;	//指针
}LNode, *LinkList;

//创建循环链表
void CreateList(LinkList &L, int Group[], int n)
{
	L = new LNode;
	L->next = NULL;
	LNode *r;
	r = L;
	for (int i = 0; i < n - 1; i++)
	{
		LNode *p;
		p = new LNode;
		p->data = Group[i];
		p->position = i + 1;
		p->next = NULL;
		r->next = p;
		r = p;
	}
	LNode *p;
	p = new LNode;
	p->data = Group[n - 1];
	p->position = n;
	p->next = L->next;
	r->next = p;
}

//返回最大子数组
SArray Compare(LinkList L, int Length)
{
	SArray MaxSum[N][2];
	//MaxSum[N][0].Sdata表示前N-1个数中，最大的子数组
	//MaxSum[N][1].Sdata表示前N-1个数的最大的子数组和加第N个数的和与第N个数相比的最大值
	LNode *r;
	r = L->next;
	MaxSum[0][0].Sdata = MaxSum[0][1].Sdata = r->data;
	MaxSum[0][0].start = MaxSum[0][1].start = r->position;
	MaxSum[0][0].end = MaxSum[0][1].end = r->position;
	for (int i = 1; i < Length; i++)
	{
		if (MaxSum[i - 1][0].Sdata > MaxSum[i - 1][1].Sdata)
		{
			MaxSum[i][0].Sdata = MaxSum[i - 1][0].Sdata;
			MaxSum[i][0].start = MaxSum[i - 1][0].start;
			MaxSum[i][0].end = MaxSum[i - 1][0].end;
		}
		else
		{
			MaxSum[i][0].Sdata = MaxSum[i - 1][1].Sdata;
			MaxSum[i][0].start = MaxSum[i - 1][1].start;
			MaxSum[i][0].end = MaxSum[i - 1][1].end;
		}
		if (MaxSum[i - 1][1].Sdata + r->next->data > r->next->data)
		{
			MaxSum[i][1].Sdata = MaxSum[i - 1][1].Sdata + r->next->data;
			MaxSum[i][1].start = MaxSum[i - 1][1].start;
			MaxSum[i][1].end = r->next->position;
		}
		else
		{
			MaxSum[i][1].Sdata = r->next->data;
			MaxSum[i][1].start = r->next->position;
			MaxSum[i][1].end = r->next->position;
		}
		r = r->next;
	}
	if (MaxSum[Length - 1][0].Sdata > MaxSum[Length - 1][1].Sdata)
	{
		return MaxSum[Length - 1][0];
	}
	else
	{
		return MaxSum[Length - 1][1];
	}
}

//将含n个数的循环数组依次从各个点断开，产生n个含n个数组的单链数组
SArray Divide(LinkList L, int length)
{
	LinkList LGroup[N];	//头节点集合
	LNode *r;
	r = L;
	for (int i = 0; i < length; i++)
	{
		LGroup[i] = r;
		r = r->next;
	}
	SArray MaxGroup[N];	//分成的各个数组的最大子数组的集合
	for (int i = 0; i < length; i++)
	{
		MaxGroup[i].Sdata = Compare(LGroup[i], length).Sdata;
		MaxGroup[i].start = Compare(LGroup[i], length).start;
		MaxGroup[i].end = Compare(LGroup[i], length).end;
	}
	SArray Max = MaxGroup[0];	//各个数组的最大子数组和的最大值
	for (int i = 1; i < length; i++)
	{
		if (Max.Sdata < MaxGroup[i].Sdata)
		{
			Max.Sdata = MaxGroup[i].Sdata;
			Max.start = MaxGroup[i].start;
			Max.end = MaxGroup[i].end;

		}
	}
	return Max;
}

int main()
{
	int Number[N];	//整数数组
	int length;	//数组长度
	cout << "请输入一个整型数组：" << endl;
	cin >> Number[0];
	length = 1;
	while (getchar() != '\n')
	{
		cin >> Number[length++];
	}
	LinkList L;
	CreateList(L, Number, length);
	cout << "该数组中的最大的子数组和为：";
	cout << Divide(L, length).Sdata << endl;
	cout << "该最大子数组的起始位置为：";
	cout << Divide(L, length).start << endl;
	cout << "该最大子数组的终止位置为：";
	cout << Divide(L, length).end << endl;
	return 0;
}