#include<iostream>
#include<ctime>
using namespace std;

struct calcu
{
	int fuhao;		//0,1,2,3分别代表+，-，*，/
	int firNum;		//算式的第一个数
	int lastNum;	//算式的第二个数
	int intORfen;	//0,1分别代表整数运算和真分数运算
};

void main()
{
	srand((unsigned)time(NULL));
	calcu num[30];
	int i;
	for (i = 0; i < 30; i++)
	{
		num[i].firNum = rand()%100;	//四则运算的第一个数
		num[i].lastNum = rand()%100;	//四则运算的第二个数
		num[i].fuhao = rand() % 4;	//四则运算的运算符
		num[i].intORfen = rand() % 2;	
		if (num[i].fuhao == 1)	//当运算符为-时
		{
			if (num[i].firNum < num[i].lastNum)
			{
				int mNum = num[i].firNum;
				num[i].firNum = num[i].lastNum;
				num[i].lastNum = mNum;
			}
		}
		if (num[i].fuhao == 3)	//当运算符为/时
		{
			if (num[i].lastNum == 0)
			{
				i = i - 1;
			}
		}
	}
	for (i = 0; i < 30; i++)
	{
		//整数四则运算
		if (num[i].intORfen == 0)	
		{
			switch (num[i].fuhao)
			{
			case 0:cout << num[i].firNum << " + " << num[i].lastNum << " = " << endl; break;
			case 1:cout << num[i].firNum << " - " << num[i].lastNum << " = " << endl; break;
			case 2:cout << num[i].firNum << " * " << num[i].lastNum << " = " << endl; break;
			case 3:cout << num[i].firNum << " / " << num[i].lastNum << " = " << endl;
			}
		}
		//真分数四则运算
		else 
		{
			int addnum1 = rand() % 20+1;
			int addnum2 = rand() % 20+1;
			switch (num[i].fuhao)
			{
			case 0:cout << num[i].firNum << "/" << num[i].firNum + addnum1 << " + " << num[i].lastNum << "/" << num[i].lastNum + addnum2 << " = " << endl; break;
			case 1:cout << num[i].firNum << "/" << num[i].firNum + addnum1 << " - " << num[i].lastNum << "/" << num[i].lastNum + addnum2 << " = " << endl; break;
			case 2:cout << "(" << num[i].firNum << "/" << num[i].firNum + addnum1 << ") * (" << num[i].lastNum << "/" << num[i].lastNum + addnum2 << ") = " << endl; break;
			case 3:cout << "(" << num[i].firNum << "/" << num[i].firNum + addnum1 << ") / (" << num[i].lastNum << "/" << num[i].lastNum + addnum2 << ") = " << endl;
			}
		}
	}
}