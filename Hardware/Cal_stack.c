#include"Cal_stack.h"

//ջ�ĳ�ʼ��
int InitStack_op(SqStack_op* S)
{
	S->base_op = (char*)malloc(MAXSIZE * sizeof(char));
	if (!S->base_op) exit(0);
	S->top_op = S->base_op;           // ��ʼ��topָ��base
	S->stacksize = MAXSIZE;     // ����ջ���������
	return 1;
}

int InitStack(SqStack* S)
{
	S->base = (double*)malloc(MAXSIZE * sizeof(double));
	if (!S->base) exit(0);
	S->top = S->base;           
	S->stacksize = MAXSIZE;     
	return 1;
}

//�ж�˳��ջ�Ƿ�Ϊ��
int StackEmpty_op(SqStack_op* S)
{
	if (S->top_op == S->base_op)
		return 0;
	else
		return 1;
}

int StackEmpty(SqStack* S)
{
	if (S->top == S->base)
		return 1;
	else
		return 0;
}

//��e����ջ
int Push_op(SqStack_op* S, char e)
{
	if (S->top_op - S->base_op == S->stacksize) // ջ�����
		return 0;
	*S->top_op++ = e;  // Ԫ����ջ���ƶ�ջ��ָ��
	return 1;
}

int Push(SqStack* S, double e)
{
	if (S->top - S->base == S->stacksize) 
		return 0;
	*S->top = e;  
	S->top++;
	return 1;
}

//�Ƴ�ջ��������һ��ֵ����e
int Pop_op(SqStack_op* S, char* e)
{
	if (S->top_op == S->base_op) // ջ�ռ��
		return 0;
	*e = *--S->top_op;  
	return 1;
}

int Pop(SqStack* S, double* e)
{
	if (S->top == S->base) 
		return 0;
	*e = *--S->top;  
	return 1;
}

//��ȡջ��Ԫ��
char GetTop_op(SqStack_op* S)
{
	char ret = *(S->top_op - 1);
	return ret;
}

double GetTop(SqStack* S)
{
	double ret = *(S->top - 1);
	return ret;
}

//ջ�����
int DestroyStark(SqStack* S)
{
	if (S->base)
	{
		free(S->base);
		S->stacksize = 0;
		S->base = S->top = NULL;
	}
	return 1;
}

int DestroyStark_op(SqStack_op* S)
{
	if (S->base_op)
	{
		free(S->base_op);
		S->stacksize = 0;
		S->base_op = S->top_op = NULL;
	}
	return 1;
}

int ClearStark(SqStack* S)
{
	if (S->base) S->top = S->base;
	return 1;
}

int ClearStark_op(SqStack_op* S)
{
	if (S->base_op) S->top_op = S->base_op;
	return 1;
}