#include"Cal_algorithm.h"
//字符优先级函数
int precedence(char op)
{
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
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

//字符分析函数，分别将数字字符与运算字符分开放入两个栈中

void extract(char str[], SqStack_op* _op, SqStack* _Value)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')continue;//去除空格
		if (isdigit(str[i]))//查找数字字符
		{
			double _val = 0;
			while (str[i] != '\0' && isdigit(str[i]))
			{
				_val = (_val * 10) + (str[i] - '0');
				i++;
			}
			Push(_Value, _val);//将数字字符转为double类型的数放如栈中
			i--;//因为for会再加一次
		}
		else if (str[i] == '.')
		{
			i++;//将i移到'.'后的数
			if (isdigit(str[i]))//查找数字字符
			{
				double val = 0;
				double temp = 0;
				int n = 1;
				while (str[i] != '\0' && isdigit(str[i]))
				{
					n = n * 10;
					val += (double)(str[i] - '0') / n;
					i++;

				}
				Pop(_Value, &temp);//出栈将'.'前的值赋值给temp
				Push(_Value, val + temp);//入栈将'.'前后的数相加并存入栈中
			}
			i--;//因为for会再加一次
		}
		else
		{
			while (StackEmpty_op(_op) && precedence(GetTop_op(_op)) >= precedence(str[i]))//栈是否为空和字符优先级判断
			{
				double val1;
				double val2;
				Pop(_Value, &val1);
				Pop(_Value, &val2);
				char op;
				Pop_op(_op, &op);

				double temp1 = applyOp(val2, val1, op);
				Push(_Value, temp1);

			}
			Push_op(_op, str[i]);

		}
	}

	while (StackEmpty_op(_op))//将栈中剩下的值计算完成
	{
		double val1;
		double val2;
		Pop(_Value, &val1);
		Pop(_Value, &val2);

		char op;
		Pop_op(_op, &op);

		double temp1 = applyOp(val2, val1, op);
		Push(_Value, temp1);//最后将最终值放入栈顶
	}
}

