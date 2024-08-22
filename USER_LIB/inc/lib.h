#ifndef __LIB_H_
#define __LIB_H_

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f4xx.h"
#include "gpio.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "sdram.h"

#include "ltdc.h"
#include "lcd.h"


void function_goto(int (*pfunction)());         //function switch
int system_init();                                      //mian in c
int __main();                                   //main in c++

/*例程函数*/
void MY_NVIC_SetVectorTable(u32 NVIC_VectTab,u32 Offset);
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group);
void GPIO_Set(GPIO_TypeDef* GPIOx,u32 BITx,u32 MODE,u32 OTYPE,u32 OSPEED,u32 PUPD);
void GPIO_AF_Set(GPIO_TypeDef* GPIOx,u8 BITx,u8 AFx);
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group);

#ifdef __cplusplus
 }
#endif


#endif

