#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"

#define  LED_SET(dat)    GPIO_Write(GPIOF, dat)


extern uint8_t led_flow_flag;    //流水灯开启标志

void LED_Hardware_Init(void);	//LED初始化
void LED_Flow(void);

#endif

