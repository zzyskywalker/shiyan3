#include "exti.h"
#include "led.h"

/*******************************
��  �ܣ��ⲿ�ж�����
��  ������
����ֵ����
*******************************/
void EXTI_Configure(void)
{
		GPIO_InitTypeDef GPIO_TypeDefStructure;
		EXTI_InitTypeDef EXTI_TypeDefStructure;
		NVIC_InitTypeDef NVIC_TypeDefStructure;
		
		//�����ж�����˿�ʱ��
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		
		//�����ⲿ�ж�ʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
		
		GPIO_TypeDefStructure.GPIO_Pin = GPIO_Pin_8;
		GPIO_TypeDefStructure.GPIO_Mode = GPIO_Mode_IN;     //ͨ������ģʽ
		GPIO_TypeDefStructure.GPIO_PuPd = GPIO_PuPd_UP; 	  //����
		GPIO_Init(GPIOB, &GPIO_TypeDefStructure);

		//�ж��߹���
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource8);
		
		EXTI_TypeDefStructure.EXTI_Line = EXTI_Line8;
		EXTI_TypeDefStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_TypeDefStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
		EXTI_TypeDefStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_TypeDefStructure);
		
		//EXT9_5_IRQn�ж��������ȼ�����
		NVIC_TypeDefStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
		NVIC_TypeDefStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_TypeDefStructure.NVIC_IRQChannelSubPriority = 7;
		NVIC_TypeDefStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_TypeDefStructure);
}



/*******************************
��  �ܣ��ⲿ�жϷ�����                  ������p8��Ҳ����key2
��  ������
����ֵ����
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



