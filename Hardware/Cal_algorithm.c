#include"Cal_algorithm.h"
//�ַ����ȼ�����
int precedence(char op)
{
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	return 0;
}

//ͨ���ַ���ѡ��Ҫ���е�����
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

//�����ֺ������Ǳ�������Ϊf(x) = x * x
//ԭ���ο�����������������������
//����ָ�Ϊn��С��������� �Ƚ�n = 10000
//���� ��Ϊ�ú����Ļ�������

double Integrate(double a, double b)
{
	//�ָ�ĸ�����nԽ�󾫶�Խ��
	int n = 10000;

	//���ڴ��ݽ��
	double A = 0;

	//���㲿��
	double h = (b - a) / n;

	//û��ý�ʲô
	double temp = a;

	//�������֮��
	for (int i = 0; i < n; i++)
	{
		A += Cumulative_function(temp) * h;
		temp += h;
	}

	return A;
}

//�����������̣�����������
//�����Լ���f(x) = x * x�Ļ���
double Cumulative_function(double x)
{
	return x * x;
}

//�ַ������������ֱ������ַ��������ַ��ֿ���������ջ��

void extract(char str[], SqStack_op* _op, SqStack* _Value)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')continue;//ȥ���ո�
		if (isdigit(str[i]))//���������ַ�
		{
			double _val = 0;
			while (str[i] != '\0' && isdigit(str[i]))
			{
				_val = (_val * 10) + (str[i] - '0');
				i++;
			}
			Push(_Value, _val);//�������ַ�תΪdouble���͵�������ջ��
			i--;//��Ϊfor���ټ�һ��
		}
		else if (str[i] == '.')
		{
			i++;//��i�Ƶ�'.'�����
			if (isdigit(str[i]))//���������ַ�
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
				Pop(_Value, &temp);//��ջ��'.'ǰ��ֵ��ֵ��temp
				Push(_Value, val + temp);//��ջ��'.'ǰ�������Ӳ�����ջ��
			}
			i--;//��Ϊfor���ټ�һ��
		}
		else
		{
			while (StackEmpty_op(_op) && precedence(GetTop_op(_op)) >= precedence(str[i]))//ջ�Ƿ�Ϊ�պ��ַ����ȼ��ж�
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

	while (StackEmpty_op(_op))//��ջ��ʣ�µ�ֵ�������
	{
		double val1;
		double val2;
		Pop(_Value, &val1);
		Pop(_Value, &val2);

		char op;
		Pop_op(_op, &op);

		double temp1 = applyOp(val2, val1, op);
		Push(_Value, temp1);//�������ֵ����ջ��
	}
}

