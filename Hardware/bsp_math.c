#include "stm32f10x.h"                  // Device header
#include "math.h"
#include "bsp_key.h"
#include "OLED.h"
#include "bsp_math.h"
/*按键布局*/
long long Keyboard[16]={
	1,2,3,'*',
	4,5,6,'-',
	7,8,9,'+',
	'=',0,'.','/'
};
//栈的初始化
void Stack_Init(Stack *s)
{ 
	s->Top=-1;
}

//符号栈的初始化
void operate_Init(operate *o)
{ 
	o->top=-1;
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

//判断符号栈是否已满
int operate_Full(operate *o)
{
	if(o->top==Max-1)
	{
	return 1;
	}
	return 0;
}

//数字入栈
void Stack_push(Stack *s,double Value)
{
	if(Full(s))
	{
	return ;
	}
	s->data[++(s->Top)]=Value ;

}

//符号入栈
void operate_push(operate *o,double Value)
{
	if(operate_Full(o))
	{
	return ;
	}
	o->operate_data[++(o->top)]=Value ;

}

//计算数值函数
long long calculate(Stack *s)
{
	long long result=0;
	int nten=0;
	for(int i=s->Top;i>=0;i--)
	{
	result +=s->data[i]*pow(10,nten);
	nten++;
	}

	return result ;
}

//按键输入函数
void Input(void)
{
	static Stack NumInput;//定义为静态变量，防止每次定义的时候都初始化
	static operate opInput;
	static int InitFlag = 1;
	static int X=1;
    if (InitFlag) {
        Stack_Init(&NumInput);
		operate_Init (&opInput);
        InitFlag = 0;
    }
	long long Value;//要入栈的数
	uint8_t KeyValue=KeyNumGet();
	if(KeyValue)
	{
		Value=Keyboard[KeyValue-1];
		if(KeyValue == 4 || KeyValue == 8 || KeyValue == 12 || KeyValue == 16)
		{
            //Stack_push(&NumInput, (double)Num1);
            operate_push(&opInput, (char)Value); // 操作符入栈
			OLED_ShowChar(X,1, Value, OLED_8X16);
			X+=8;
            Stack_Init(&NumInput); // 清空操作数栈，开始新操作数的输入
		}
		else
		{
		
		Stack_push(&NumInput ,Value);
		OLED_ShowNum(X,1,Value,1,OLED_8X16);
		long long Num1 = calculate(&NumInput);
		X+=8;
		}
		
	
	}
		OLED_Update();
	
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





