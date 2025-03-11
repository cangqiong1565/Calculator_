#include "stm32f10x.h"                  // Device header
#include "math.h"
#include "bsp_key.h"
#include "OLED.h"
#include "bsp_math.h"

/*按键布局*/
uint8_t Keynum[16]={
	1,2,3,12,
	4,5,6,13,
	7,8,9,14,
	10,0,11,15
};
//栈的初始化
void Stack_Init(Stack *s)
{ 
	s->Top=-1;
}
//入栈
void Stack_push(Stack *s,double Value)
{
	if(s->Top==-1)
	{
	return ;
	}
	s->data[(s->Top)++]=Value ;

}
//判断栈是否已满
int Full(Stack *s)
{
	if(s->Top==Max-1)
	{
	return 1;
	}
	return 0;
}

//计算数值函数
double calculate(Stack *s)
{
	double result=0;
	double nten=0;
	for(int i=s->Top;i!=0;i--)
	{
	result +=s->data[s->Top]*pow(10,nten);
	nten++;
	}

	return result ;
}

//按键输入函数
void Input(void)
{
	Stack NumInput;
	Stack_Init(&NumInput );
	double result;
	
	int KeyValue=Keynum[KeyNumGet ()-1];
	if(KeyNumGet ())
	{
		Stack_push(&NumInput ,KeyValue );
		result=calculate(&NumInput );
	}

	OLED_ShowNum(1,1,result,NumInput.Top,OLED_8X16);
}


/*double input(void)
{
	double Number[100]={0};//存储信息的数组，最高支持一百位
	uint8_t number;//按键对应的数字
	int index=0;
	double result=0;
	
 	if(KeyNumGet())
	{
		number=Keynum[KeyNumGet()-1];
		
		for(int i=index;i!=0;i--)
		{
		Number[i]=Number[i-1];
		}
		
		Number[0]=number;
		index++;
		
	}
	
	for(int i=0;i<=index;i++)
	{
	result+=Number[i]*pow(10,i);
	}
	
	OLED_Clear ();
	OLED_ShowNum(1,1,result,index,OLED_8X16);
	OLED_Update();
}*/





