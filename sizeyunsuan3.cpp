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
//构造运算式结构体把算式存入字符串
struct Formula
{
	string str;
	int data;
};
int length = 0;//运算数个数
int fuh;//表示运算符的数（0、1、2、3分别代表+、-、*、/）
subject sub[N];//所有算式
int lpoint1;//内层左括号的位置
int rpoint1;//内层右括号的位置
int lpoint2;//外层左括号的位置
int rpoint2;//外层右括号的位置
Formula Formul[N];	//定义一个字符串数组
int Flength;	//字符串数组长度
int i, j;
int Result;	//算式的运算结果

//顺序栈数值栈的定义
typedef struct
{
	int *base;
	int *top;
	int stacksize;
}SqStack;
SqStack OPND;
//顺序栈数值栈的初始化
bool InitStack(SqStack &OPND)
{
	OPND.base = new int[N];
	if (!OPND.base)
	{
		exit(OVERFLOW);
	}
	OPND.top = OPND.base;
	OPND.stacksize = N;
	return true;
}
//数值栈入栈
bool Push(SqStack &OPND, int &e)
{
	if (OPND.top - OPND.base == OPND.stacksize)
	{
		return false;
	}
	*OPND.top++ = e;
	return true;
}
//数值栈出栈
bool Pop(SqStack &OPND, int &e)
{
	if (OPND.top == OPND.base)
	{
		return false;
	}
	e = *--OPND.top;
	return true;
}
//数值栈取栈顶元素
int GetTop(SqStack OPND)
{
	if (OPND.top == OPND.base)
	{
		exit(1);
	}
	return *(OPND.top - 1);
}

//顺序栈符号栈的定义
typedef struct
{
	string *fubase;
	string *futop;
	int fustacksize;
}fuSqStack;
fuSqStack OPTR;
//顺序栈符号栈的初始化
bool fuInitStack(fuSqStack &OPTR)
{
	OPTR.fubase = new string[N];
	if (!OPTR.fubase)
	{
		exit(OVERFLOW);
	}
	OPTR.futop = OPTR.fubase;
	OPTR.fustacksize = N;
	return true;
}
//符号栈入栈
bool fuPush(fuSqStack &OPTR, string e)
{
	if (OPTR.futop - OPTR.fubase == OPTR.fustacksize)
	{
		return false;
	}
	*OPTR.futop++ = e;
	return true;
}
//符号栈出栈
bool fuPop(fuSqStack &OPTR, string &e)
{
	if (OPTR.futop == OPTR.fubase)
	{
		return false;
	}
	e = *--OPTR.futop;
	return true;
}
//符号栈取栈顶元素
string fuGetTop(fuSqStack OPTR)
{
	if (OPTR.futop == OPTR.fubase)
	{
		exit(1);
	}
	return *(OPTR.futop - 1);
}

//将算式转化为string数组
void ToString(subject sub, int length, Formula Formul[], int &Flength)
{
	Flength = -1;
	for (j = 0; j < length; j++)
	{
		if (sub.arith[j].left2 != "")
		{
			Flength += 1;
			Formul[Flength].str = sub.arith[j].left2;
		}
		if (sub.arith[j].left1 != "")
		{
			Flength += 1;
			Formul[Flength].str = sub.arith[j].left1;
		}
		Flength += 1;
		Formul[Flength].str = to_string(sub.arith[j].member);
		Formul[Flength].data = sub.arith[j].member;
		if (sub.arith[j].right1 != "")
		{
			Flength += 1;
			Formul[Flength].str = sub.arith[j].right1;
		}
		if (sub.arith[j].right2 != "")
		{
			Flength += 1;
			Formul[Flength].str = sub.arith[j].right2;
		}
		if (sub.arith[j].fuhao != "")
		{
			Flength += 1;
			Formul[Flength].str = sub.arith[j].fuhao;
		}
	}
}

//比较优先级
string Precede(string Fuhao1, string Fuhao2)
{
	string FuResult;	//返回优先级关系">"、"<"、"="
	if (Fuhao1 == "+")
	{
		if (Fuhao2 == "+" || Fuhao2 == "-" || Fuhao2 == ")" || Fuhao2 == "#")
		{
			FuResult = ">";
		}
		else
		{
			FuResult = "<";
		}
	}
	if (Fuhao1 == "-")
	{
		if (Fuhao2 == "+" || Fuhao2 == "-" || Fuhao2 == ")" || Fuhao2 == "#")
		{
			FuResult = ">";
		}
		else
		{
			FuResult = "<";
		}
	}
	if (Fuhao1 == "*")
	{
		if (Fuhao2 == "(")
		{
			FuResult = "<";
		}
		else
		{
			FuResult = ">";
		}
	}
	if (Fuhao1 == "/")
	{
		if (Fuhao2 == "(")
		{
			FuResult = "<";
		}
		else
		{
			FuResult = ">";
		}
	}
	if (Fuhao1 == "(")
	{
		if (Fuhao2 == ")")
		{
			FuResult = "=";
		}
		else
		{
			FuResult = "<";
		}
	}
	if (Fuhao1 == ")")
	{
		FuResult = ">";
	}
	if (Fuhao1 == "#")
	{
		if (Fuhao2 == "#")
		{
			FuResult = "=";
		}
		else
		{
			FuResult = "<";
		}
	}
	return FuResult;
}

//两个数运算
int Operate(int num1, string theta, int num2)
{
	int InResult;	//返回运算结果
	if (theta == "+")
	{
		InResult = num1 + num2;
	}
	else if (theta == "-")
	{
		InResult = num1 - num2;
	}
	else if (theta == "*")
	{
		InResult = num1*num2;
	}
	else
	{
		InResult = num1 / num2;
	}
	return InResult;
}

//表达式求值
int ValueResult(subject sub, int length)
{
	int i;
	Flength = 0;
	string PResult;	//优先级比较结果
	string theta;	//出栈符号
	int num1, num2;	//出栈运算数
	ToString(sub, length, Formul, Flength);
	Formul[Flength].str = "#";
	InitStack(OPND);
	fuInitStack(OPTR);
	fuPush(OPTR, "#");
	for (i = 0; i <= Flength; i++)
	{
		if (Formul[i].str == "#")
		{
			while (*OPTR.futop != "#")
			{
				PResult = Precede(fuGetTop(OPTR), Formul[i].str);
				if (PResult == ">")
				{
					fuPop(OPTR, theta);
					Pop(OPND, num2);
					Pop(OPND, num1);
					int num3 = Operate(num1, theta, num2);
					Push(OPND, num3);
				}
				else if (PResult == "<")
				{
					fuPush(OPTR, Formul[i].str);
				}
				else
				{
					fuPop(OPTR, theta);
				}
			}
		}
		else if (Formul[i].str == "(" || Formul[i].str == ")" || Formul[i].str == "+" || Formul[i].str == "-" || Formul[i].str == "*" || Formul[i].str == "/")
		{
			PResult = Precede(fuGetTop(OPTR), Formul[i].str);
			if (PResult == ">")
			{
				fuPop(OPTR, theta);
				Pop(OPND, num2);
				Pop(OPND, num1);
				int num3 = Operate(num1, theta, num2);
				Push(OPND, num3);
				PResult = Precede(fuGetTop(OPTR), Formul[i].str);
				if (PResult == "=")
				{
					fuPop(OPTR, theta); continue;
				}
				else
				{
					fuPush(OPTR, Formul[i].str);
				}
			}
			else if (PResult == "<")
			{
				fuPush(OPTR, Formul[i].str);
			}
			else
			{
				fuPop(OPTR, theta);
			}
		}
		else
		{
			Push(OPND, Formul[i].data);
		}
	}
	return GetTop(OPND);
}

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
			cout << "选择错误！" << endl;
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
			cout << "选择错误！" << endl;
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

//初始化算式
void Init(subject &sub, int &length, int high, int low, int TwoOrFour)
{
	length = rand() % 9 + 2;
	for (j = 0; j < length - 1; j++)
	{
		sub.arith[j].left2 = "";
		sub.arith[j].left1 = "";
		sub.arith[j].right1 = "";
		sub.arith[j].right2 = "";
		sub.arith[j].member = rand() % (high - low) + low;
		//无乘除法
		if (TwoOrFour == 2)
		{
			fuh = rand() % 2;
		}
		//有乘除法
		if (TwoOrFour == 4)
		{
			fuh = rand() % 4;
		}
		sub.arith[j].fuhao = Fuhao(fuh);
	}
	sub.arith[length - 1].left2 = "";
	sub.arith[length - 1].left1 = "";
	sub.arith[length - 1].right1 = "";
	sub.arith[length - 1].right2 = "";
	sub.arith[length - 1].member = rand() % (high - low) + low;
	sub.arith[length - 1].fuhao = "=";
	for (j = 0; j < length; j++)
	{
		if (sub.arith[j].right1 == "" || sub.arith[j].right1 == ")")
		{
			if (sub.arith[j].fuhao == "/"&&sub.arith[j].left2 == ""&&sub.arith[j].left1 == ""&&sub.arith[j].right2 == "")
			{
				if (sub.arith[j + 1].fuhao == "/"&&sub.arith[j + 1].left2 == ""&&sub.arith[j + 1].left1 == ""&&sub.arith[j + 1].right1 == ""&&sub.arith[j + 1].right2 == "")
				{
					sub.arith[j].left1 = "(";
					sub.arith[j + 1].right1 = ")";
					j += 1;
				}
			}
		}
	}
}

//输出函数
void Output(subject sub, int length)
{
	for (j = 0; j < length; j++)
	{
		cout << sub.arith[j].left2 << sub.arith[j].left1 << sub.arith[j].member << sub.arith[j].right1 << sub.arith[j].right2 << sub.arith[j].fuhao;
	}
	cout << endl;
}

//括号的产生
int Bracket(subject &sub, int length)
{
	int check = 0;
	if (length > 2)
	{
		int floor = rand() % 2 + 1;//产生括号的层数
		if (floor == 1)
		{
			lpoint1 = rand() % (length - 1);//产生左括号的位置
			rpoint1 = lpoint1 + rand() % (length - 1 - lpoint1);//产生右括号的位置
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
			sub.arith[lpoint1].left1 = "(";
			sub.arith[rpoint1].right1 = ")";
		}
		else
		{
			if (length > 3)
			{
				lpoint1 = rand() % (length - 1);//产生内层左括号的位置
				rpoint1 = lpoint1 + rand() % (length - 1 - lpoint1);//产生内层右括号的位置
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
				sub.arith[lpoint1].left1 = "(";
				sub.arith[rpoint1].right1 = ")";
				if (lpoint1 == 0)
				{
					lpoint2 = lpoint1;//产生外层左括号的位置
				}
				else
				{
					lpoint2 = lpoint1 - rand() % lpoint1;//产生外层左括号的位置
				}
				rpoint2 = rpoint1 + rand() % (length - rpoint1);//产生外层右括号的位置
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
				sub.arith[lpoint2].left2 = "(";
				sub.arith[rpoint2].right2 = ")";
			}
			else
			{
				check = 1;
			}
		}
	}
	return check;
}

//用户输入计算结果
int Input()
{
	int answer;
	cout << "请输入计算结果：";
	cin >> answer;
	return answer;
}

//判断用户是否答对
int Right(int result, int answer, int &count)
{
	if (answer == result)
	{
		cout << "######恭喜您！回答正确！" << endl;
		count++;
	}
	else
	{
		cout << "******很遗憾！回答错误！";
		cout << "正确答案为：" << result << endl;
	}
	return 0;
}

//输出用户答题结果
void UserResult(int count)
{
	cout << "!!!!!!答题完毕！" << endl;
	cout << "!!!!!!您答对题数为：" << count << endl;
}

//验证除法有无余数
int change(subject &sub, int length)
{
	int check = 0;
	for (j = 0; j < length; j++)
	{
		if (sub.arith[j].fuhao == "/"&&sub.arith[j].right1 != ")")
		{
			if (sub.arith[j].member%sub.arith[j + 1].member != 0)
			{
				check = 1;
			}
		}
		if (sub.arith[j].fuhao == "/"&&sub.arith[j].right1 == ")")
		{
			if ((sub.arith[j - 1].member / sub.arith[j].member) % sub.arith[j + 1].member != 0)
			{
				check = 1;
			}
		}
	}
	return check;
}

//有乘除法、有括号、加减有负数、除法有余数
void Output1(int number, int low, int high)
{
	int count = 0;
	for (i = 0; i < number; i++)
	{
		int check = 0;//检验产生式是否合格
		Init(sub[i], length, high, low, 4);
		Result = ValueResult(sub[i], length);
		check = Bracket(sub[i], length);
		if (Result>high)
		{
			check = 1;
		}
		if (check == 1)
		{
			i = i - 1; continue;
		}
		else
		{
			Output(sub[i], length);
			int answer = Input();
			Right(Result, answer, count);
		}
	}
	UserResult(count);
}
//有乘除法、有括号、加减有负数、除法无余数
void Output2(int number, int low, int high)
{
	int count = 0;
	for (i = 0; i < number; i++)
	{
		int check = 0;//检验产生式是否合格
		int check1 = 0;//检验除法是否有余数
		Init(sub[i], length, high, low, 4);
		check = Bracket(sub[i], length);
		check1 = change(sub[i], length);
		Result = ValueResult(sub[i], length);
		if (Result > high)
		{
			check = 1;
		}
		if (check == 1 || check1 == 1)
		{
			i = i - 1; continue;
		}
		else
		{
			Output(sub[i], length);
			int answer = Input();
			Right(Result, answer, count);
		}
	}
	UserResult(count);
}
//有乘除法、有括号、加减无负数、除法有余数
void Output3(int number, int low, int high)
{
	int count = 0;
	for (i = 0; i < number; i++)
	{
		int check = 0;//检验产生式是否合格
		Init(sub[i], length, high, low, 4);
		check = Bracket(sub[i], length);
		Result = ValueResult(sub[i], length);
		if (Result < 0 || Result > high)
		{
			check = 1;
		}
		if (check == 1)
		{
			i = i - 1; continue;
		}
		else
		{
			Output(sub[i], length);
			int answer = Input();
			Right(Result, answer, count);
		}
	}
	UserResult(count);
}
//有乘除法、有括号、加减无负数、除法无余数
void Output4(int number, int low, int high)
{
	int count = 0;
	for (i = 0; i < number; i++)
	{
		int check = 0;//检验产生式是否合格
		int check1 = 0;//检验除法是否有余数
		Init(sub[i], length, high, low, 4);
		check = Bracket(sub[i], length);
		check1 = change(sub[i], length);
		Result = ValueResult(sub[i], length);
		if (Result < 0 || Result > high)
		{
			check = 1;
		}
		if (check == 1 || check1 == 1)
		{
			i = i - 1; continue;
		}
		else
		{
			Output(sub[i], length);
			int answer = Input();
			Right(Result, answer, count);
		}
	}
	UserResult(count);
}
//有乘除法、无括号、加减有负数、除法有余数
void Output5(int number, int low, int high)
{
	int count = 0;
	for (i = 0; i < number; i++)
	{
		int check = 0;
		Init(sub[i], length, high, low, 4);
		Result = ValueResult(sub[i], length);
		if (Result > high)
		{
			check = 1;
		}
		if (check == 1)
		{
			i = i - 1; continue;
		}
		Output(sub[i], length);
		int answer = Input();
		Right(Result, answer, count);
	}
	UserResult(count);
}
//有乘除法、无括号、加减有负数、除法无余数
void Output6(int number, int low, int high)
{
	int count = 0;
	for (i = 0; i < number; i++)
	{
		int check = 0;
		Init(sub[i], length, high, low, 4);
		check = change(sub[i], length);
		Result = ValueResult(sub[i], length);
		if (Result > high)
		{
			check = 1;
		}
		if (check == 1)
		{
			i = i - 1; continue;
		}
		Output(sub[i], length);
		int answer = Input();
		Right(Result, answer, count);
	}
	UserResult(count);
}
//有乘除法、无括号、加减无负数、除法有余数
void Output7(int number, int low, int high)
{
	int count = 0;
	for (i = 0; i < number; i++)
	{
		int check = 0;//检验
		Init(sub[i], length, high, low, 4);
		Result = ValueResult(sub[i], length);
		if (Result < 0 || Result > high)
		{
			check = 1;
		}
		if (check == 1)
		{
			i = i - 1;
		}
		else
		{
			Output(sub[i], length);
			int answer = Input();
			Right(Result, answer, count);
		}
	}
	UserResult(count);
}
//有乘除法、无括号、加减无负数、除法无余数
void Output8(int number, int low, int high)
{
	int count = 0;
	for (i = 0; i < number; i++)
	{
		int check = 0;//检验
		Init(sub[i], length, high, low, 4);
		Result = ValueResult(sub[i], length);
		check = change(sub[i], length);
		if (Result < 0 || Result > high)
		{
			check = 1;
		}
		if (check == 1)
		{
			i = i - 1; continue;
		}
		else
		{
			Output(sub[i], length);
			int answer = Input();
			Right(Result, answer, count);
		}
	}
	UserResult(count);
}
//无乘除法、有括号、加减有负数
void Output9(int number, int low, int high)
{
	int count = 0;
	for (i = 0; i < number; i++)
	{
		int check = 0;//检验产生式是否合格
		Init(sub[i], length, high, low, 2);
		Result = ValueResult(sub[i], length);
		check = Bracket(sub[i], length);
		if (Result>high)
		{
			check = 1;
		}
		if (check == 1)
		{
			i = i - 1; continue;
		}
		else
		{
			Output(sub[i], length);
			int answer = Input();
			Right(Result, answer, count);
		}
	}
	UserResult(count);
}
//无乘除法、有括号、加减无负数
void Output10(int number, int low, int high)
{
	int count = 0;
	for (i = 0; i < number; i++)
	{
		int check = 0;//检验产生式是否合格
		Init(sub[i], length, high, low, 2);
		check = Bracket(sub[i], length);
		Result = ValueResult(sub[i], length);
		if (Result < 0 || Result > high)
		{
			check = 1;
		}
		if (check == 1)
		{
			i = i - 1; continue;
		}
		else
		{
			Output(sub[i], length);
			int answer = Input();
			Right(Result, answer, count);
		}
	}
	UserResult(count);
}
//无乘除法、无括号、加减有负数
void Output11(int number, int low, int high)
{
	int count = 0;
	for (i = 0; i < number; i++)
	{
		Init(sub[i], length, high, low, 2);
		Result = ValueResult(sub[i], length);
		if (Result>high)
		{
			i = i - 1; continue;
		}
		Output(sub[i], length);
		int answer = Input();
		Right(Result, answer, count);
	}
	UserResult(count);
}
//无乘除法、无括号、加减无负数
void Output12(int number, int low, int high)
{
	int count = 0;//记录用户答对题数
	for (i = 0; i < number; i++)
	{
		Init(sub[i], length, high, low, 2);
		int check = 0;//检验
		Result = ValueResult(sub[i], length);
		if (Result<0 || Result>high)
		{
			check = 1;
		}
		if (check == 1)
		{
			i = i - 1; continue;
		}
		Output(sub[i], length);
		int answer = Input();
		Right(Result, answer, count);
	}
	UserResult(count);
}

int main()
{
	srand((unsigned)time(NULL));
	int chooseWay;	//条件筛选结果
	int number;	//题目数量
	int low;	//算式数值范围的最小值
	int high;	//算式数值范围的最大值
	cout << "请输入出题数量：";
	cin >> number;
	cout << "请输入算式的数值范围：" << endl;
	cout << "最小值：";
	cin >> low;
	cout << "最大值：";
	cin >> high;
	chooseWay = Choose();		//条件筛选
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
	case 12:Output12(number, low, high);
	}
	return 0;
}