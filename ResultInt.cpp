//返回一个整数数组中最大子数组的和
#include<iostream>
#define N 100
using namespace std;

int Compare(int Group[], int Length)
{
	int MaxSum[N][2];
	//MaxSum[N][0]表示前N-1个数中，最大的子数组和
	//MaxSum[N][1]表示前N-1个数的最大的子数组和加第N个数的和与第N个数相比的最大值
	MaxSum[0][0] = MaxSum[0][1] = Group[0];
	for (int i = 1; i < Length; i++)
	{
		MaxSum[i][0] = __max(MaxSum[i - 1][0], MaxSum[i - 1][1]);
		MaxSum[i][1] = __max(MaxSum[i - 1][1] + Group[i], Group[i]);
	}
	return __max(MaxSum[Length - 1][0], MaxSum[Length - 1][1]);
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
	cout << "该数组中的最大的子数组和为：";
	cout << Compare(Number, length) << endl;
	return 0;
}