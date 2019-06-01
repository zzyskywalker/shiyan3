/********************************************************************
ʵ�����ƣ�����ܶ�̬ɨ��ʵ��

Ӳ��ģ�飺�����ԭ��Ӧ��ʵ����

Ӳ�����ߣ�ARM P11�ӿ�---------����� P4�ӿ� 
			PC0--------SI
			PC1--------RCK
			PC2--------SCK
			PC3--------A
			PC4--------B
			PC5--------C
		 ARM P10�ӿ�----------���� P1�ӿ�
             PB8--------KEY1_N
             PB11-------KEY2_N	
          ARM P12�ӿ�-----------LED P2�ӿ�
             PF0~PF7------LED1~LED8		 
         ע������20P����ֱ��P11��P4�ӿڣ�ֱ��P10��P1�ӿڣ�ֱ��P12��P2�ӿڡ�
					
ʵ���������������ʾ����0~7����ͨ�������������ⲿ�жϴ�����ˮ�ơ�

����ʱ�䣺2018-10-31
************************************************************************/
#include "stm32f4xx.h"
#include "delay.h"
#include "smg.h"
#include "led.h"
#include "exti.h"
#include "my_timer.h"

#define KEY  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)
 
void Key_Hardware_Init()
{
	GPIO_InitTypeDef GPIO_TypeDefStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);	//�����ж�����˿�ʱ��

	GPIO_TypeDefStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_TypeDefStructure.GPIO_Mode = GPIO_Mode_IN;    //ͨ������ģʽ
	GPIO_TypeDefStructure.GPIO_PuPd = GPIO_PuPd_UP; 	 //����
	GPIO_Init(GPIOB, &GPIO_TypeDefStructure);
}


int main(void)
{
	uint8_t i;
	uint16_t cont = 0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	Delay_Init();             //��ʱ��ʼ��
	EXTI_Configure();         //�ⲿ�жϳ�ʼ�� 
	TIM1_Configure(999, 167);  //��ʱ����ʼ��  1ms
	SMG_Init();               //����ܳ�ʼ��
	LED_Hardware_Init();       //LED�Ƴ�ʼ�� 
	Key_Hardware_Init();       //��������ʼ��
	 
	while(1)
	{
		cont++;
		if(cont >= 500)
		{
			cont = 0;
			SMG_Sele(i);  //�������ʾ����
			if(i == 5)    //�����������ʾ������λʱ�������
			{
				if(!KEY)
				{
					Delay_Ms(10);
					if(!KEY)
					{
						while(!KEY){};
						led_flow_flag = 1;   //������ˮ��
					}
			    }
			}
			i++;
			if(i>9)
			{
				i=0;
			}
	
		}
		Delay_Ms(2);   //��Ҫ����Ч��ʱ����ʱ 
		LED_Flow();   
	}
}

//end file



