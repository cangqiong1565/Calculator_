#include "stm32f10x.h"                  // Device header
#include "OLED.h"
uint8_t KeyNum=0;
/*矩阵按键初始化*/
void MatrixKey_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*矩阵按键扫描*/
uint8_t MatrixKey_Scan(void)
{
	
    uint8_t KeyValue = 0;
    uint8_t i;

    // 逐列扫描
    for (i = 0; i < 4; i++)
    {
       
        GPIO_Write(GPIOA, ~(0x10 << i));

        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
        {
            KeyValue = i * 4 + 1;
        }
        else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0)
        {
            KeyValue = i * 4 + 2;
        }
        else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0)
        {
            KeyValue = i * 4 + 3;
        }
        else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0)
        {
            KeyValue = i * 4 + 4;
        }
    }
	
    return KeyValue;
}

/*定时器按键扫描*/
void MatrixKey_Tick(void)
{
	static uint8_t Count;
	static uint8_t CurrState,PrevState;
	
	Count++;
	if(Count>=20)
	{
		Count=0;
		PrevState = CurrState ;
		CurrState = MatrixKey_Scan();
		
		if(CurrState==0&&PrevState !=0)
		{
		KeyNum = PrevState ;
		}
	
	
	}


}

uint8_t KeyNumGet(void)
{
	uint8_t Temp;
	Temp=KeyNum ;
	KeyNum =0;
	return Temp ;


}
