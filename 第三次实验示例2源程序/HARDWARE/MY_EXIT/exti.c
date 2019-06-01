#include "exti.h"
#include "led.h"

/*******************************
功  能：外部中断配置
参  数：无
返回值：无
*******************************/
void EXTI_Configure(void)
{
		GPIO_InitTypeDef GPIO_TypeDefStructure;
		EXTI_InitTypeDef EXTI_TypeDefStructure;
		NVIC_InitTypeDef NVIC_TypeDefStructure;
		
		//开启中断输入端口时钟
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		
		//开启外部中断时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
		
		GPIO_TypeDefStructure.GPIO_Pin = GPIO_Pin_8;
		GPIO_TypeDefStructure.GPIO_Mode = GPIO_Mode_IN;     //通用输入模式
		GPIO_TypeDefStructure.GPIO_PuPd = GPIO_PuPd_UP; 	  //上拉
		GPIO_Init(GPIOB, &GPIO_TypeDefStructure);

		//中断线关联
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource8);
		
		EXTI_TypeDefStructure.EXTI_Line = EXTI_Line8;
		EXTI_TypeDefStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_TypeDefStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
		EXTI_TypeDefStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_TypeDefStructure);
		
		//EXT9_5_IRQn中断向量优先级设置
		NVIC_TypeDefStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
		NVIC_TypeDefStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_TypeDefStructure.NVIC_IRQChannelSubPriority = 7;
		NVIC_TypeDefStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_TypeDefStructure);
}



/*******************************
功  能：外部中断服务函数                  按键是p8，也就是key2
参  数：无
返回值：无
*******************************/
void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line8))
    {
        if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 0)
        {
            led_flow_flag = 2;
            EXTI_ClearITPendingBit(EXTI_Line8);
        }
    }
}



