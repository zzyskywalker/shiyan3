#include "led.h"
#include "delay.h"

uint8_t led_flow_flag = 0;    //��ˮ�ƿ�����־
/*******************************
��  �ܣ�LED�˿ڳ�ʼ��
��  ������
����ֵ����
*******************************/
void LED_Configure(void)
{
		GPIO_InitTypeDef   GPIO_InitStructure;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);   //����GPIOC��ʱ��
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;          //���ģʽ
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         //������� 
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
		cont &= 0x07;    //����7������
	}else
	{
	    LED_SET(0xC00);//0000 0001 0000 0000 ����D6��D3�������Ҳ����˵һλ���������ƣ���ʱ��
		delay_ms(300);
	}
}
//end file
