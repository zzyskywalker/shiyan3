#ifndef __LED_H
#define __LED_H
#include "sys.h"
#include "stm32f4xx.h"

#define  LED_SET(dat)    GPIO_Write(GPIOC, dat)
extern uint8_t led_flow_flag;    //��ˮ�ƿ�����־
//LED�˿�

void LED_Configure(void);
void LED_Flow(void);
#endif
