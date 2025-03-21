#include "stm32f10x.h"                  // Device header
#include "bsp_Key.h"
#include "bsp_OLED.h"
#include "math.h"
#include "bsp_math.h"
#include "bsp_Timer.h"
#include "Cal_algorithm.h"
#include "Cal_stack.h"
char arr[100];
int flag = 0;//±êÖ¾Î»
SqStack_op _op;
SqStack _Value;
SqStack *Value=&_Value;
int main (void)
{
	
	
	
		int i=0;
		Timer_Init ();
		MatrixKey_Init();
		OLED_Init();
		for(int i=0;i<64;i++)
		{
		OLED_Clear ();
		OLED_DrawCircle (64,32,i+10,OLED_UNFILLED );
		OLED_DrawCircle (64,32,2*i,OLED_UNFILLED );
		OLED_DrawCircle (64,32,3*i,OLED_UNFILLED );
		
		OLED_Update();
		}
		
		InitStack_op(&_op);
		InitStack(&_Value);
		
	
	while (1)
	{
		Input ();
		if(flag)
		{
			extract(arr, &_op, &_Value);
			OLED_ShowFloatNum(0 , 18, GetTop(&_Value), 3, 2, OLED_8X16);
			OLED_Update();
			flag = 0;
		}
		
//		extract()
	}
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		Key_Tick();
		MatrixKey_Tick();
	    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}


}

