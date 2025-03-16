#include "stm32f10x.h"                  // Device header
#include "math.h"
#include "bsp_key.h"
#include "OLED.h"
#include "bsp_math.h"
/*按键布局*/
char Keyboard[16]={
	'1','2','3','*',
	'4','5','6','-',
	'7','8','9','+',
	'=','0','.','/'
};
//栈的初始化
void Stack_Init(Stack *s)
{ 
	s->Top=-1;
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

//入栈
void Stack_push(Stack *s, char Value)
{
    if (Full(s))
    {
        return;
    }
    s->data[++(s->Top)] = Value;
    s->data[s->Top + 1] = '\0'; // 添加字符串结束符
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
	static Stack _NumInput;//定义为静态变量，防止每次定义的时候都初始化
	static int InitFlag = 1;
    if (InitFlag) {
        Stack_Init(&_NumInput);
        InitFlag = 0;
    }
	char _Value;//要入栈的数
	uint8_t KeyValue=KeyNumGet();
	if(KeyValue)
	{
		_Value=Keyboard[KeyValue-1];
		if(KeyValue)
		{
			Stack_push(&_NumInput ,_Value);
			OLED_ShowString(1,1,_NumInput.data,OLED_8X16);
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





