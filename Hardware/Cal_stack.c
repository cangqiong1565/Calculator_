#include"Cal_stack.h"

//栈的初始化
int InitStack_op(SqStack_op* S)
{
	S->base_op = (char*)malloc(MAXSIZE * sizeof(char));
	if (!S->base_op) exit(0);
	S->top_op = S->base_op;           // 初始化top指向base
	S->stacksize = MAXSIZE;     // 设置栈的最大容量
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

//判断顺序栈是否为空
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

//将e推入栈
int Push_op(SqStack_op* S, char e)
{
	if (S->top_op - S->base_op == S->stacksize) // 栈满检查
		return 0;
	*S->top_op++ = e;  // 元素入栈并移动栈顶指针
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

//推出栈，并将下一个值传给e
int Pop_op(SqStack_op* S, char* e)
{
	if (S->top_op == S->base_op) // 栈空检查
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

//获取栈顶元素
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

//栈的清空
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