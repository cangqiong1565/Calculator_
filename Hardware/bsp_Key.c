#include "stm32f10x.h"                  // Device header
#include "bsp_OLED.h"
static uint8_t KeyNum=0;
/*矩阵按键初始化*/
void MatrixKey_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*矩阵按键扫描*/
uint8_t MatrixKey_Scan(void)
{
    uint8_t _KeyValue = 0;
    uint8_t i;

    // 逐列扫描
    for (i = 0; i < 4; i++)
    {
        GPIO_Write(GPIOA, ~(0x10 << i));
        if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
        {
            _KeyValue = i * 4 + 1;
        }
        else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0)
        {
            _KeyValue = i * 4 + 2;
        }
        else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0)
        {
            _KeyValue = i * 4 + 3;
        }
        else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0)
        {
            _KeyValue = i * 4 + 4;
        }
		
    }
	
    return _KeyValue;
}

//10号按键扫描
uint8_t Key_GetState(void)
{
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == 0)
		{
		   return 17;
		}
	else if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
		{
		   return 18;
		}
	else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10) == 0)
		{
		   return 19;
		}
		else if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == 0)
		{
		   return 20;
		}
	
		
		return 0;
	
}

/*定时器按键扫描*/
void MatrixKey_Tick(void)
{
	static uint8_t _Count;
	static uint8_t _CurrState,_PrevState;
	
	_Count++;
	if(_Count>=20)
	{
		_Count=0;
		_PrevState = _CurrState ;
		_CurrState = MatrixKey_Scan();
		
		if(_CurrState==0&&_PrevState !=0)
		{
		KeyNum = _PrevState ;
		}
	}
}

/*定时器按键扫描*/
void Key_Tick(void)
{
	static uint8_t _Count;
	static uint8_t _CurrState,_PrevState;
	
	_Count++;
	if(_Count>=20)
	{
		_Count=0;
		_PrevState = _CurrState ;
		_CurrState = Key_GetState();
		
		if(_CurrState==0&&_PrevState !=0)
		{
		KeyNum = _PrevState ;
		}
	}
}

uint8_t KeyNumGet(void)
{
	uint8_t _Temp;
	_Temp=KeyNum ;
	KeyNum =0;
	return _Temp ;
}
