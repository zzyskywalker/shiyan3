/***********************************************************************
实验名称：中断实验

硬件模块：计算机原理应用实验箱

硬件接线：ARM P12接口---------按键 P1接口 	
           PF8------------K1_N  
				ARM P11接口----------LED P2接口	 
           PC0------------LED1
         注：可用20P排线直连P12、P1接口，可用20P排线直连P11、P2接口。
		   
实验现象：按键KEY1触发外部中断，LED1电平翻转。

更新时间：2018-10-31
***********************************************************************/
#include "stm32f4xx.h"
#include "exti.h"
#include "led.h"
#include "delay.h"


/*******************************
功  能：外部中断服务函数
参  数：无
返回值：无
*******************************/
void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line8))
    {
        if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8) == 0)
        {
            led_flow_flag=!led_flow_flag;
            EXTI_ClearITPendingBit(EXTI_Line8);
        }
    }
}


int main(void)
{   
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);   
		LED_Configure();      //LED端口配置
		EXTI_Configure();     //外部中断配置
	  GPIO_Write(GPIOC, 0x00FF);
	  delay_Init();
		led_flow_flag=0;
		
    while(1)
    {
				LED_Flow(); 
    }

}

//end file

