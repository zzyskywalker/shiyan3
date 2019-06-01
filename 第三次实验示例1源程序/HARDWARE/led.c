#include "led.h"
#include "delay.h"

uint8_t led_flow_flag = 0;    //流水灯开启标志
/*******************************
功  能：LED端口初始化
参  数：无
返回值：无
*******************************/
void LED_Configure(void)
{
		GPIO_InitTypeDef   GPIO_InitStructure;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);   //开启GPIOC的时钟
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;          //输出模式
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         //推挽输出 
		GPIO_InitStructure.GPIO_Speed = GPIO_Medium_Speed;     
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	
		GPIO_Write(GPIOC, 0x0000);
}
void LED_Flow(void)
{
    static uint8_t cont;
	static uint16_t led_data;
	if(led_flow_flag == 0)
	{ 
		led_data = 1<<cont;         
		LED_SET(led_data); 
		delay_ms(100);
		cont++;
		cont &= 0x07;    //大于7后清零
	}else
	{
	    LED_SET(0xC00);//0000 0001 0000 0000 控制D6和D3红灯亮，也就是说一位控制两个灯，逆时针
		delay_ms(300);
	}
}
//end file
