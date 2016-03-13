#include<iostream>
#include<string>
#include<ctime>
#define N 100
using namespace std;

//构造四则运算的结构体
struct  arithmetic
{
	string left2;//第二层（外层）左括号
	string left1;//第一层（内层）左括号
	int member;//运算数
	string right1;//第一层（内层）右括号
	string right2;//第二层（外层）右括号
	string fuhao;//运算符
};
//构造出题的结构体
struct subject
{
	arithmetic arith[10];
};
int length;//运算数个数
int fuh;//表示运算符的数（0、1、2、3分别代表+、-、*、/）
subject sub[N];//所有算式
int i, j;

//条件控制选择
int Choose()
{
	int chooseWay;	//条件筛选结果
	int choose1;	//有无乘除法选择
	cout << "请选择是否有乘除法（是：1/否：0）：";
	cin >> choose1;
	//有乘除法
	if (choose1 == 1)
	{
		int choose21;	//有无括号选择
		cout << "请选择是否有括号（是：1/否：0）：";
		cin >> choose21;
		//有括号
		if (choose21 == 1)
		{
			int choose31;	//加减有无负数选择
			cout << "请选择加减有无负数（有：1/无：0）：";
			cin >> choose31;
			//有负数
			if (choose31 == 1)
			{
				int choose41;	//除法有无余数选择
				cout << "除法有无余数（有：1/无：0）";
				cin >> choose41;
				//有余数
				if (choose41 == 1)
				{
					chooseWay = 1;
				}
				//无余数
				else if (choose41 == 0)
				{
					chooseWay = 2;
				}
				else
				{
					cout << "选择错误！" << endl;
					Choose();
				}
			}
			//无负数
			else if (choose31 == 0)
			{
				int choose42;	//除法有无余数选择
				cout << "除法有无余数（有：1/无：0）";
				cin >> choose42;
				//有余数
				if (choose42 == 1)
				{
					chooseWay = 3;
				}
				//无余数
				else if (choose42 == 0)
				{
					chooseWay = 4;
				}
				else
				{
					cout << "选择错误！" << endl;
					Choose();
				}
			}
			else
			{
				cout << "选择错误！" << endl;
				Choose();
			}
		}
		//无括号
		else if (choose21 == 0)
		{
			int choose32;	//加减有无负数选择
			cout << "请选择加减有无负数（有：1/无：0）：";
			cin >> choose32;
			//有负数
			if (choose32 == 1)
			{
				int choose43;	//除法有无余数选择
				cout << "除法有无余数（有：1/无：0）";
				cin >> choose43;
				//有余数
				if (choose43 == 1)
				{
					chooseWay = 5;
				}
				//无余数
				else if (choose43 == 0)
				{
					chooseWay = 6;
				}
				else
				{
					cout << "选择错误！" << endl;
					Choose();
				}
			}
			//无负数
			else if (choose32 == 0)
			{
				int choose44;	//除法有无余数选择
				cout << "除法有无余数（有：1/无：0）";
				cin >> choose44;
				//有余数
				if (choose44 == 1)
				{
					chooseWay = 7;
				}
				//无余数
				else if (choose44 == 0)
				{
					chooseWay = 8;
				}
				else
				{
					cout << "选择错误！" << endl;
					Choose();
				}
			}
			else
			{
				cout << "选择错误！" << endl;
				Choose();
			}
		}
		else
		{
			cout << "选择错误！"<<endl;
			Choose();
		}
	}
	//无乘除法
	else if (choose1 == 0)
	{
		int choose22;	//有无括号选择
		cout << "请选择是否有括号（是：1/否：0）：";
		cin >> choose22;
		//有括号
		if (choose22 == 1)
		{
			int choose33;	//加减有无负数选择
			cout << "请选择加减有无负数（有：1/无：0）：";
			cin >> choose33;
			//有负数
			if (choose33 == 1)
			{
				chooseWay = 9;
			}
			//无负数
			else if (choose33 == 0)
			{
				chooseWay = 10;
			}
			else
			{
				cout << "选择错误！" << endl;
				Choose();
			}
		}
		//无括号
		else if (choose22 == 0)
		{
			int choose34;	//加减有无负数选择
			cout << "请选择加减有无负数（有：1/无：0）：";
			cin >> choose34;
			//有负数
			if (choose34 == 1)
			{
				chooseWay = 11;
			}
			//无负数
			else if (choose34 == 0)
			{
				chooseWay = 12;
			}
			else
			{
				cout << "选择错误！" << endl;
				Choose();
			}
		}
		else
		{
			cout << "选择错误！"<<endl;
		}
	}
	else
	{
		cout << "选择错误！" << endl;
		Choose();
	}
	return chooseWay;
}

//随机数产生运算符
string Fuhao(int fuh)
{
	string fuh0;//返回运算符号
	if (fuh == 0)
		fuh0 = "+";
	else if (fuh == 1)
		fuh0 = "-";
	else if (fuh == 2)
		fuh0 = "*";
	else
		fuh0 = "/";
	return fuh0;
}

//有乘除法、有括号、加减有负数、除法有余数
void Output1(int number,int low,int high)
{
	for (i = 0; i < number; i++)
	{
		int check = 0;//检验产生式是否合格
		length = rand() % 9 + 2;
		for (j = 0; j < length - 1; j++)
		{
			sub[i].arith[j].left2 = "";
			sub[i].arith[j].left1 = "";
			sub[i].arith[j].right1 = "";
			sub[i].arith[j].right2 = "";
			sub[i].arith[j].member = rand() % high;
			fuh = rand() % 4;
			sub[i].arith[j].fuhao = Fuhao(fuh);
		}
		sub[i].arith[length - 1].left2 = "";
		sub[i].arith[length - 1].left1 = "";
		sub[i].arith[length - 1].right1 = "";
		sub[i].arith[length - 1].right2 = "";
		sub[i].arith[length - 1].member = rand() % high;
		sub[i].arith[length - 1].fuhao = "=";
		if (length > 2)
		{
			int floor = rand() % 2 + 1;//产生括号的层数
			if (floor == 1)
			{
				int lpoint1 = rand() % (length - 1);//产生左括号的位置
				int rpoint1 = lpoint1 + rand() % (length - 1 - lpoint1);//产生右括号的位置
				if (lpoint1 == rpoint1)
				{
					if (lpoint1 > 0)
					{
						lpoint1 -= 1;
					}
					else
					{
						if (rpoint1 < length - 1)
						{
							rpoint1 += 1;
						}
					}
				}
				sub[i].arith[lpoint1].left1 = "(";
				sub[i].arith[rpoint1].right1 = ")";
			}
			else
			{
				if (length > 3)
				{
					int lpoint1 = rand() % (length - 1);//产生内层左括号的位置
					int rpoint1 = lpoint1 + 1;//产生内层右括号的位置
					sub[i].arith[lpoint1].left1 = "(";
					sub[i].arith[rpoint1].right1 = ")";
					int lpoint2 = lpoint1 - rand() % lpoint1;//产生外层左括号的位置
					int rpoint2 = rpoint1 + rand() % (length - rpoint1);//产生外层右括号的位置
					if (lpoint2 == lpoint1&&rpoint2 == rpoint1)
					{
						if (lpoint2 > 0)
						{
							lpoint2 -= 1;
						}
						else
						{
							if (rpoint2 < length - 1)
							{
								rpoint2 += 1;
							}
						}
					}
					sub[i].arith[lpoint2].left2 = "(";
					sub[i].arith[rpoint2].right2 = ")";
				}
				else
				{
					check = 1;
				}
			}
		}
		if (check == 1)
		{
			i = i - 1;
		}
		else
		{
			for (j = 0; j < length; j++)
			{
				cout << sub[i].arith[j].left2 << sub[i].arith[j].left1 << sub[i].arith[j].member << sub[i].arith[j].right1 << sub[i].arith[j].right2 << sub[i].arith[j].fuhao;
			}
			cout << endl;
		}
	}
}
//有乘除法、有括号、加减有负数、除法无余数
void Output2(int number, int low, int high)
{
}
//有乘除法、有括号、加减无负数、除法有余数
void Output3(int number, int low, int high)
{
	for (i = 0; i < number; i++)
	{
		int check = 0;//检验产生式是否合格
		length = rand() % 9 + 2;
		for (j = 0; j < length - 1; j++)
		{
			sub[i].arith[j].left2 = "";
			sub[i].arith[j].left1 = "";
			sub[i].arith[j].right1 = "";
			sub[i].arith[j].right2 = "";
			sub[i].arith[j].member = rand() % high;
			fuh = rand() % 4;
			sub[i].arith[j].fuhao = Fuhao(fuh);
		}
		sub[i].arith[length - 1].left2 = "";
		sub[i].arith[length - 1].left1 = "";
		sub[i].arith[length - 1].right1 = "";
		sub[i].arith[length - 1].right2 = "";
		sub[i].arith[length - 1].member = rand() % high;
		sub[i].arith[length - 1].fuhao = "=";
		if (length > 2)
		{
			int floor = rand() % 2 + 1;//产生括号的层数
			if (floor == 1)
			{
				int lpoint1 = rand() % (length - 1);//产生左括号的位置
				int rpoint1 = lpoint1 + rand() % (length - 1 - lpoint1);//产生右括号的位置
				if (lpoint1 == rpoint1)
				{
					if (lpoint1 > 0)
					{
						lpoint1 -= 1;
					}
					else
					{
						if (rpoint1 < length - 1)
						{
							rpoint1 += 1;
						}
					}
				}
				sub[i].arith[lpoint1].left1 = "(";
				sub[i].arith[rpoint1].right1 = ")";
			}
			else
			{
				if (length > 3)
				{
					int lpoint1 = rand() % (length - 1);//产生内层左括号的位置
					int rpoint1 = lpoint1 + 1;//产生内层右括号的位置
					sub[i].arith[lpoint1].left1 = "(";
					sub[i].arith[rpoint1].right1 = ")";
					int lpoint2 = lpoint1 - rand() % lpoint1;//产生外层左括号的位置
					int rpoint2 = rpoint1 + rand() % (length - rpoint1);//产生外层右括号的位置
					if (lpoint2 == lpoint1&&rpoint2 == rpoint1)
					{
						if (lpoint2 > 0)
						{
							lpoint2 -= 1;
						}
						else
						{
							if (rpoint2 < length - 1)
							{
								rpoint2 += 1;
							}
						}
					}
					sub[i].arith[lpoint2].left2 = "(";
					sub[i].arith[rpoint2].right2 = ")";
				}
				else
				{
					check = 1;
				}
			}
		}
		if (check == 1)
		{
			i = i - 1;
		}
		else
		{
			for (j = 0; j < length; j++)
			{
				cout << sub[i].arith[j].left2 << sub[i].arith[j].left1 << sub[i].arith[j].member << sub[i].arith[j].right1 << sub[i].arith[j].right2 << sub[i].arith[j].fuhao;
			}
			cout << endl;
		}
	}
}
//有乘除法、有括号、加减无负数、除法无余数
void Output4(int number, int low, int high)
{
}
//有乘除法、无括号、加减有负数、除法有余数
void Output5(int number, int low, int high)
{
	for (i = 0; i < number; i++)
	{
		length = rand() % 9 + 2;
		for (j = 0; j < length - 1; j++)
		{
			sub[i].arith[j].left2 = "";
			sub[i].arith[j].left1 = "";
			sub[i].arith[j].right1 = "";
			sub[i].arith[j].right2 = "";
			sub[i].arith[j].member = rand() % high;
			fuh = rand() % 4;
			sub[i].arith[j].fuhao = Fuhao(fuh);
		}
		sub[i].arith[length - 1].left2 = "";
		sub[i].arith[length - 1].left1 = "";
		sub[i].arith[length - 1].right1 = "";
		sub[i].arith[length - 1].right2 = "";
		sub[i].arith[length - 1].member = rand() % high;
		sub[i].arith[length - 1].fuhao = "=";
		for (j = 0; j < length; j++)
		{
			cout << sub[i].arith[j].left2 << sub[i].arith[j].left1 << sub[i].arith[j].member << sub[i].arith[j].right1 << sub[i].arith[j].right2 << sub[i].arith[j].fuhao;
		}
		cout << endl;
	}
}
//有乘除法、无括号、加减有负数、除法无余数
void Output6(int number, int low, int high)
{
}
//有乘除法、无括号、加减无负数、除法有余数
void Output7(int number, int low, int high)
{
	for (i = 0; i < number; i++)
	{
		length = rand() % 9 + 2;
		for (j = 0; j < length - 1; j++)
		{
			sub[i].arith[j].left2 = "";
			sub[i].arith[j].left1 = "";
			sub[i].arith[j].right1 = "";
			sub[i].arith[j].right2 = "";
			sub[i].arith[j].member = rand() % high;
			fuh = rand() % 4;
			sub[i].arith[j].fuhao = Fuhao(fuh);
		}
		sub[i].arith[length - 1].left2 = "";
		sub[i].arith[length - 1].left1 = "";
		sub[i].arith[length - 1].right1 = "";
		sub[i].arith[length - 1].right2 = "";
		sub[i].arith[length - 1].member = rand() % high;
		sub[i].arith[length - 1].fuhao = "=";
		int sum = sub[i].arith[0].member;//求和
		int check = 0;//检验减法是否为负数
		for (j = 1; j < length; j++)
		{
			if (sub[i].arith[j - 1].fuhao == "+")
			{
				sum += sub[i].arith[j].member;
			}
			else
			{
				sum -= sub[i].arith[j].member;
				if (sum < 0)
				{
					check = 1; break;
				}
			}
		}
		if (check == 1)
		{
			i = i - 1; continue;
		}
		for (j = 0; j < length; j++)
		{
			cout << sub[i].arith[j].left2 << sub[i].arith[j].left1 << sub[i].arith[j].member << sub[i].arith[j].right1 << sub[i].arith[j].right2 << sub[i].arith[j].fuhao;
		}
		cout << endl;
	}
}
//有乘除法、无括号、加减无负数、除法无余数
void Output8(int number, int low, int high)
{
}
//无乘除法、有括号、加减有负数
void Output9(int number, int low, int high)
{
	for (i = 0; i < number; i++)
	{
		int check = 0;//检验产生式是否合格
		length = rand() % 9 + 2;
		for (j = 0; j < length - 1; j++)
		{
			sub[i].arith[j].left2 = "";
			sub[i].arith[j].left1 = "";
			sub[i].arith[j].right1 = "";
			sub[i].arith[j].right2 = "";
			sub[i].arith[j].member = rand() % high;
			fuh = rand() % 2;
			sub[i].arith[j].fuhao = Fuhao(fuh);
		}
		sub[i].arith[length - 1].left2 = "";
		sub[i].arith[length - 1].left1 = "";
		sub[i].arith[length - 1].right1 = "";
		sub[i].arith[length - 1].right2 = "";
		sub[i].arith[length - 1].member = rand() % high;
		sub[i].arith[length - 1].fuhao = "=";
		if (length > 2)
		{
			int floor = rand() % 2 + 1;//产生括号的层数
			if (floor == 1)
			{
				int lpoint1 = rand() % (length - 1);//产生左括号的位置
				int rpoint1 = lpoint1 + rand() % (length - 1 - lpoint1);//产生右括号的位置
				if (lpoint1 == rpoint1)
				{
					if (lpoint1 > 0)
					{
						lpoint1 -= 1;
					}
					else
					{
						if (rpoint1 < length - 1)
						{
							rpoint1 += 1;
						}
					}
				}
				sub[i].arith[lpoint1].left1 = "(";
				sub[i].arith[rpoint1].right1 = ")";
			}
			else
			{
				if (length > 3)
				{
					int lpoint1 = rand() % (length - 1);//产生内层左括号的位置
					int rpoint1 = lpoint1 + 1;//产生内层右括号的位置
					sub[i].arith[lpoint1].left1 = "(";
					sub[i].arith[rpoint1].right1 = ")";
					int lpoint2 = lpoint1 - rand() % lpoint1;//产生外层左括号的位置
					int rpoint2 = rpoint1 + rand() % (length - rpoint1);//产生外层右括号的位置
					if (lpoint2 == lpoint1&&rpoint2 == rpoint1)
					{
						if (lpoint2 > 0)
						{
							lpoint2 -= 1;
						}
						else
						{
							if (rpoint2 < length - 1)
							{
								rpoint2 += 1;
							}
						}
					}
					sub[i].arith[lpoint2].left2 = "(";
					sub[i].arith[rpoint2].right2 = ")";
				}
				else
				{
					check = 1;
				}
			}
		}
		if (check == 1)
		{
			i = i - 1;
		}
		else
		{
			for (j = 0; j < length; j++)
			{
				cout << sub[i].arith[j].left2 << sub[i].arith[j].left1 << sub[i].arith[j].member << sub[i].arith[j].right1 << sub[i].arith[j].right2 << sub[i].arith[j].fuhao;
			}
			cout << endl;
		}
	}
}
//无乘除法、有括号、加减无负数
void Output10(int number, int low, int high)
{
	for (i = 0; i < number; i++)
	{
		int check = 0;//检验产生式是否合格
		length = rand() % 9 + 2;
		for (j = 0; j < length - 1; j++)
		{
			sub[i].arith[j].left2 = "";
			sub[i].arith[j].left1 = "";
			sub[i].arith[j].right1 = "";
			sub[i].arith[j].right2 = "";
			sub[i].arith[j].member = rand() % high;
			fuh = rand() % 2;
			sub[i].arith[j].fuhao = Fuhao(fuh);
		}
		sub[i].arith[length - 1].left2 = "";
		sub[i].arith[length - 1].left1 = "";
		sub[i].arith[length - 1].right1 = "";
		sub[i].arith[length - 1].right2 = "";
		sub[i].arith[length - 1].member = rand() % high;
		sub[i].arith[length - 1].fuhao = "=";
		if (length > 2)
		{
			int floor = rand() % 2 + 1;//产生括号的层数
			if (floor == 1)
			{
				int lpoint1 = rand() % (length-1);//产生左括号的位置
				int rpoint1 = lpoint1 + rand() % (length-1 - lpoint1);//产生右括号的位置
				if (lpoint1 == rpoint1)
				{
					if (lpoint1 > 0)
					{
						lpoint1 -= 1;
					}
					else
					{
						if (rpoint1 < length - 1)
						{
							rpoint1 += 1;
						}
					}
				}
				sub[i].arith[lpoint1].left1 = "(";
				sub[i].arith[rpoint1].right1 = ")";
			}
			else
			{
				if (length > 3)
				{
					int lpoint1 = rand() % (length - 1);//产生内层左括号的位置
					int rpoint1 = lpoint1 + 1;//产生内层右括号的位置
					sub[i].arith[lpoint1].left1 = "(";
					sub[i].arith[rpoint1].right1 = ")";
					int lpoint2 = lpoint1 - rand() % lpoint1;//产生外层左括号的位置
					int rpoint2 = rpoint1 + rand() % (length - rpoint1);//产生外层右括号的位置
					if (lpoint2 == lpoint1&&rpoint2 == rpoint1)
					{
						if (lpoint2 > 0)
						{
							lpoint2 -= 1;
						}
						else
						{
							if (rpoint2 < length - 1)
							{
								rpoint2 += 1;
							}
						}
					}
					sub[i].arith[lpoint2].left2 = "(";
					sub[i].arith[rpoint2].right2 = ")";
				}
				else
				{
					check = 1; 
				}
			}
		}
		if (check == 1)
		{
			i = i - 1; 
		}
		else
		{
			for (j = 0; j < length; j++)
			{
				cout << sub[i].arith[j].left2 << sub[i].arith[j].left1 << sub[i].arith[j].member << sub[i].arith[j].right1 << sub[i].arith[j].right2 << sub[i].arith[j].fuhao;
			}
			cout << endl;
		}		
	}
}
//无乘除法、无括号、加减有负数
void Output11(int number, int low, int high)
{
	for (i = 0; i < number; i++)
	{
		length = rand() % 9 + 2;
		for (j = 0; j < length - 1; j++)
		{
			sub[i].arith[j].left2 = "";
			sub[i].arith[j].left1 = "";
			sub[i].arith[j].right1 = "";
			sub[i].arith[j].right2 = "";
			sub[i].arith[j].member = rand() % high;
			fuh = rand() % 2;
			sub[i].arith[j].fuhao = Fuhao(fuh);
		}
		sub[i].arith[length - 1].left2 = "";
		sub[i].arith[length - 1].left1 = "";
		sub[i].arith[length - 1].right1 = "";
		sub[i].arith[length - 1].right2 = "";
		sub[i].arith[length - 1].member = rand() % high;
		sub[i].arith[length - 1].fuhao = "=";
		for (j = 0; j < length; j++)
		{
			cout << sub[i].arith[j].left2 << sub[i].arith[j].left1 << sub[i].arith[j].member << sub[i].arith[j].right1 << sub[i].arith[j].right2 << sub[i].arith[j].fuhao;
		}
		cout << endl;
	}
}
//无乘除法、无括号、加减无负数
void Output12(int number, int low, int high)
{
	for (i = 0; i < number; i++)
	{
		length = rand() % 9 + 2;
		for (j = 0; j < length - 1; j++)
		{
			sub[i].arith[j].left2 = "";
			sub[i].arith[j].left1 = "";
			sub[i].arith[j].right1 = "";
			sub[i].arith[j].right2 = "";
			sub[i].arith[j].member = rand() % high;
			fuh = rand() % 2;
			sub[i].arith[j].fuhao = Fuhao(fuh);
		}
		sub[i].arith[length - 1].left2 = "";
		sub[i].arith[length - 1].left1 = "";
		sub[i].arith[length - 1].right1 = "";
		sub[i].arith[length - 1].right2 = "";
		sub[i].arith[length - 1].member = rand() % high;
		sub[i].arith[length - 1].fuhao = "=";
		int sum = sub[i].arith[0].member;//求和
		int check=0;//检验减法是否为负数
		for (j = 1; j < length; j++)
		{
			if (sub[i].arith[j - 1].fuhao == "+")
			{
				sum += sub[i].arith[j].member;
			}
			else
			{
				sum -= sub[i].arith[j].member;
				if (sum < 0)
				{
					check = 1; break;
				}
			}
		}
		if (check == 1)
		{
			i = i - 1; continue;
		}
		for (j = 0; j < length; j++)
		{
			cout << sub[i].arith[j].left2 << sub[i].arith[j].left1 << sub[i].arith[j].member << sub[i].arith[j].right1 << sub[i].arith[j].right2 << sub[i].arith[j].fuhao;
		}
		cout << endl;
	}
}

void main()
{
	srand((unsigned)time(NULL));
	int chooseWay;	//条件筛选结果
	int number;	//题目数量
	int low;	//算式数值范围的最小值
	int high;	//算式数值范围的最大值
	cout << "请输入出题数量：";
	cin >> number;
	cout << "请输入算式的数值范围："<<endl;
	cout << "最小值：";
	cin >> low;
	cout << "最大值：";
	cin >> high;
	chooseWay=Choose();		//条件筛选
	switch (chooseWay)
	{
	case 1:Output1(number, low, high); break;
	case 2:Output2(number, low, high); break;
	case 3:Output3(number, low, high); break;
	case 4:Output4(number, low, high); break;
	case 5:Output5(number, low, high); break;
	case 6:Output6(number, low, high); break;
	case 7:Output7(number, low, high); break;
	case 8:Output8(number, low, high); break;
	case 9:Output9(number, low, high); break;
	case 10:Output10(number, low, high); break;
	case 11:Output11(number, low, high); break;
	case 12:Output12(number, low, high); break;
	}
}