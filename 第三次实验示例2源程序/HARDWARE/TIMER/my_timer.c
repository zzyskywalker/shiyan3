#include "my_timer.h"
#include "led.h"

/******************************************
��  �ܣ���ʱ��1��ʼ��
��  ����arr  ��ʱ����ֵ  psc  Ԥ��Ƶϵ��
����ֵ����
******************************************/
void TIM1_Configure(uint32_t arr,uint16_t psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
    
    //��ʱ����ֵ
    TIM_TimeBaseStructure.TIM_Period = arr;
    //Ԥ����ϵ��
    TIM_TimeBaseStructure.TIM_Prescaler = psc;
    //���ϼ���
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    //ʱ�ӷ�Ƶ����
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    //�ظ���������
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
    
    //ѡ���ж�����
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
    //��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    //��Ӧ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;
    //ʹ���ж�����
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    //TIM1�ж�ʹ��
    TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
    //TIM1ʹ��
    TIM_Cmd(TIM1,ENABLE);
}

/******************************************
��  �ܣ���ʱ��1�жϷ�����
��  ������
����ֵ����
******************************************/
void TIM1_UP_TIM10_IRQHandler(void)
{
    static uint16_t cont_time = 0;
    if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
    {
       if(led_flow_flag)
	   {
	      cont_time++;
		  if(cont_time >= 5000)
		  {
		     cont_time = 0;
			 led_flow_flag = 0;
		  }
	   }
       TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
    }
}

