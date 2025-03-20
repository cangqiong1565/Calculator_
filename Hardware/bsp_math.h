#ifndef __BSP_MATH_H
#define __BSP_MATH_H

enum {Max=100};

static char Keyboard[20]={
	'7','8','9','*',
	'4','5','6','-',
	'1','2','3','+',
	'/','0','.','=',
	'T','#','S','C'
	
};
typedef struct
{
	char data[Max];
	int Top;//栈顶指针
}Stack;
static void Stack_Init(Stack *s);
static int Full(Stack *s);
static void Stack_push(Stack *s,char Value);
long long calculate(Stack *s);
void Input(void);
char* GetInput(void);



#endif
