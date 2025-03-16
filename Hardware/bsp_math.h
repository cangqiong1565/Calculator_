#ifndef __BSP_MATH_H
#define __BSP_MATH_H

#define Max 100
typedef struct
{
	char data[Max];
	int Top;//栈顶指针
}Stack;
void Stack_Init(Stack *s);
int Full(Stack *s);
void Stack_push(Stack *s,char Value);
long long calculate(Stack *s);
void Input(void);



#endif
