#include "stm32f10x.h"                  // Device header
#include "bsp_Key.h"
#include "OLED.h"
#include "math.h"
#include "bsp_math.h"

int caculater[100];
char mathoperator[5]={'+','-','*','/','='};


int main (void)
{
	
		OLED_Init();
	
		for(int i=0;i<64;i++)
		{
		OLED_Clear ();
		OLED_DrawCircle (64,32,i+10,OLED_UNFILLED );
		OLED_DrawCircle (64,32,2*i,OLED_UNFILLED );
		OLED_DrawCircle (64,32,3*i,OLED_UNFILLED );
		
		OLED_Update();
		}
		
	
	while (1)
	{
		
		
		
		OLED_Update();
	}
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		MatrixKey_Tick();
		
		
		
		
	    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}


}

