/***********************************************************************
ʵ�����ƣ��ж�ʵ��

Ӳ��ģ�飺�����ԭ��Ӧ��ʵ����

Ӳ�����ߣ�ARM P12�ӿ�---------���� P1�ӿ� 	
           PF8------------K1_N  
				ARM P11�ӿ�----------LED P2�ӿ�	 
           PC0------------LED1
         ע������20P����ֱ��P12��P1�ӿڣ�����20P����ֱ��P11��P2�ӿڡ�
		   
ʵ�����󣺰���KEY1�����ⲿ�жϣ�LED1��ƽ��ת��

����ʱ�䣺2018-10-31
***********************************************************************/
#include "stm32f4xx.h"
#include "exti.h"
#include "led.h"
#include "delay.h"


/*******************************
��  �ܣ��ⲿ�жϷ�����
��  ������
����ֵ����
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
		LED_Configure();      //LED�˿�����
		EXTI_Configure();     //�ⲿ�ж�����
	  GPIO_Write(GPIOC, 0x00FF);
	  delay_Init();
		led_flow_flag=0;
		
    while(1)
    {
				LED_Flow(); 
    }

}

//end file

