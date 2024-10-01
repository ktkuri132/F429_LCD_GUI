#include <stm32f4xx.h>
#include <touch.h>
#include <JY61_usart6.h>
#include <usart.h>

void BSP_Init()
{
    delay_init(180);
    //uart_init(90,115200);
    USART1_Init(115200);
    USART2_Init(115200);
    SDRAM_Init();
    LCD_Init();
    gt9xxx_init();
    EXTI_Configuration();
    
    
}