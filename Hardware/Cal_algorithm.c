#include"Cal_algorithm.h"

float const Pi = 3.14;
//�ַ����ȼ�����
int precedence(char op)
{
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	if (op == 'S' || op == 'C') return 3;
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

//�ַ������������ֱ������ַ��������ַ��ֿ���������ջo

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
		if (_str[i] == ' ')continue;//ȥ���ո�
		if (isdigit(_str[i]))//���������ַ�
		{
			_GetIntNum = 0;
			while (_str[i] != '\0' && isdigit(_str[i]))
			{
				_GetIntNum = (_GetIntNum * 10) + (_str[i] - '0');
				i++;
			}
			Push(_Stack_Num, _GetIntNum);//�������ַ�תΪdouble���͵�������ջ��
			i--;//��Ϊfor���ټ�һ��
		}
		else if (_str[i] == '.')
		{
			i++;//��i�Ƶ�'.'�����
			if (isdigit(_str[i]))//���������ַ�
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
				Pop(_Stack_Num, &temp);//��ջ��'.'ǰ��ֵ��ֵ��temp
				Push(_Stack_Num, _GetFlNum + temp);//��ջ��'.'ǰ�������Ӳ�����ջ��
			}
			i--;//��Ϊfor���ټ�һ��
		}
		else
		{
			//ջ�Ƿ�Ϊ�պ��ַ����ȼ��жϲ���ջ�е�ֵ���г������㲢����ջ��
			while (StackEmpty_op(_Stack_Op) && precedence(GetTop_op(_Stack_Op)) >= precedence(_str[i]))
			{

				Pop(_Stack_Num, &_FirstNum);


				Pop_op(_Stack_Op, &op);

				Pop(_Stack_Num, &_LastNum);


				if (op != 'S' && op != 'C')
				{
					temp1 = applyOp(_LastNum, _FirstNum, op);
					Push(_Stack_Num, temp1);//�������ֵ����ջ��
				}
				else
				{
					temp2 = Trig(op, _FirstNum);
					Push(_Stack_Num, temp2);//�������ֵ����ջ��
				}


			}
			Push_op(_Stack_Op, _str[i]);

		}
	}
		while (StackEmpty_op(_Stack_Op))//��ջ��ʣ�µ�ֵ�������
		{
	


			Pop(_Stack_Num, &_FirstNum);
	
	
			Pop_op(_Stack_Op, &op);
	
			Pop(_Stack_Num, &_LastNum);
	
	
			if (op != 'S' && op != 'C')
			{
				temp1 = applyOp(_LastNum, _FirstNum, op);
				Push(_Stack_Num, temp1);//�������ֵ����ջ��
			}
			else
			{
				temp2 = Trig(op, _FirstNum);
				Push(_Stack_Num, temp2);//�������ֵ����ջ��
			}
	
		}
}
//�������ȼ��㺯��
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