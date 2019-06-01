#include "led.h"
#include "delay.h"

uint8_t led_flow_flag = 0;    //流水灯开启标志

/**********************************************************
*功  能：LED初始化
*参  数：无
*返回值：无
**********************************************************/
void LED_Hardware_Init(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);   //开启GPIOF的时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;          //输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         //推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Medium_Speed;     //速率25MHz
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	GPIO_Write(GPIOF, 0x0000);
}


void LED_Flow(void)
{
    static uint8_t cont;
	static uint16_t led_data;
	if(led_flow_flag == 0)
	{
		LED_SET(0x0000);
	}
	else if(led_flow_flag == 1)
	{
		led_data = 1<<cont;         
		LED_SET(led_data); 
		Delay_Ms(100);
		cont++;
		cont &= 0x07;    //大于7后清零
	}else if(led_flow_flag == 2)
	{
	    LED_SET(0xff00);
		Delay_Ms(300);
		LED_SET(0x0000);
		Delay_Ms(300);
	}
}


