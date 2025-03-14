#ifndef __BSP_MATH_H
#define __BSP_MATH_H

#define Max 100
typedef struct
{
	double data[Max];
	int Top;//栈顶指针
}Stack;

typedef struct
{
	char operate_data[Max];
	int top;
}operate;

void Stack_Init(Stack *s);
int Full(Stack *s);
void Stack_push(Stack *s,double Value);
long long calculate(Stack *s);
void Input(void);



#endif
