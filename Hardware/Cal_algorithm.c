#include"Cal_algorithm.h"

float const Pi = 3.14;
//字符优先级函数
int precedence(char op)
{
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	if (op == 'S' || op == 'C') return 3;
	return 0;
}

//通过字符来选择要进行的运算
double applyOp(double a, double b, char op)
{
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
	case '#': return Integrate(a, b);
	}
	return 0;
}

//定积分函数先是被积函数为f(x) = x * x
//原理：参考高数的用曲边梯形面积求解
//将其分割为n个小矩形来求解 先将n = 10000
//参数 都为该函数的积分区间

double Integrate(double a, double b)
{
	//分割的个数，n越大精度越高
	int n = 10000;

	//用于传递结果
	double A = 0;

	//计算部长
	double h = (b - a) / n;

	//没想好叫什么
	double temp = a;

	//计算面积之和
	for (int i = 0; i < n; i++)
	{
		A += Cumulative_function(temp) * h;
		temp += h;
	}

	return A;
}

//被积函数方程，先用来总括
//先试试计算f(x) = x * x的积分
double Cumulative_function(double x)
{
	return x * x;
}

//字符分析函数，分别将数字字符与运算字符分开放入两个栈o

void extract(char _str[], SqStack_op* _Stack_Op, SqStack*_Stack_Num)
{

	double _FirstNum;
	double _LastNum;
	double temp1;
	double temp2;
	double _GetIntNum;
	double _GetFlNum;
	char op;


	for (int i = 0; _str[i] != '\0'; i++)
	{
		if (_str[i] == ' ')continue;//去除空格
		if (isdigit(_str[i]))//查找数字字符
		{
			_GetIntNum = 0;
			while (_str[i] != '\0' && isdigit(_str[i]))
			{
				_GetIntNum = (_GetIntNum * 10) + (_str[i] - '0');
				i++;
			}
			Push(_Stack_Num, _GetIntNum);//将数字字符转为double类型的数放如栈中
			i--;//因为for会再加一次
		}
		else if (_str[i] == '.')
		{
			i++;//将i移到'.'后的数
			if (isdigit(_str[i]))//查找数字字符
			{
				_GetFlNum = 0;
				double temp = 0;
				int n = 1;
				while (_str[i] != '\0' && isdigit(_str[i]))
				{
					n = n * 10;
					_GetFlNum += (double)(_str[i] - '0') / n;
					i++;

				}
				Pop(_Stack_Num, &temp);//出栈将'.'前的值赋值给temp
				Push(_Stack_Num, _GetFlNum + temp);//入栈将'.'前后的数相加并存入栈中
			}
			i--;//因为for会再加一次
		}
		else
		{
			//栈是否为空和字符优先级判断并将栈中的值进行初步计算并放如栈中
			while (StackEmpty_op(_Stack_Op) && precedence(GetTop_op(_Stack_Op)) >= precedence(_str[i]))
			{

				Pop(_Stack_Num, &_FirstNum);


				Pop_op(_Stack_Op, &op);

				Pop(_Stack_Num, &_LastNum);


				if (op != 'S' && op != 'C')
				{
					temp1 = applyOp(_LastNum, _FirstNum, op);
					Push(_Stack_Num, temp1);//最后将最终值放入栈顶
				}
				else
				{
					temp2 = Trig(op, _FirstNum);
					Push(_Stack_Num, temp2);//最后将最终值放入栈顶
				}


			}
			Push_op(_Stack_Op, _str[i]);

		}
	}
		while (StackEmpty_op(_Stack_Op))//将栈中剩下的值计算完成
		{
	


			Pop(_Stack_Num, &_FirstNum);
	
	
			Pop_op(_Stack_Op, &op);
	
			Pop(_Stack_Num, &_LastNum);
	
	
			if (op != 'S' && op != 'C')
			{
				temp1 = applyOp(_LastNum, _FirstNum, op);
				Push(_Stack_Num, temp1);//最后将最终值放入栈顶
			}
			else
			{
				temp2 = Trig(op, _FirstNum);
				Push(_Stack_Num, temp2);//最后将最终值放入栈顶
			}
	
		}
}
//整数长度计算函数
void splitNumber(int* int_long, int* porint_long, double num)
{
	int temp = num;

	if (num > temp)
	{
		*porint_long = 3;
	}
	else
	{
		*porint_long = 0;
	}

	for (*int_long = 0; temp != 0;(*int_long)++)
	{
		temp /= 10;
	}


}

double Trig(char a, double b)
{
	switch (a)
	{
		case'S':return sin(b * Pi/180);
		case'C':return cos(b * Pi / 180);

	}
}