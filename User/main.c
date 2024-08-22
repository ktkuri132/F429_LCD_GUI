#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"
#include "lib.h"
#include "usart.h"

int system_init(void)
{
    delay_init(180);
    uart_init(90,115200);
    SDRAM_Init();
    LCD_Init();
    function_goto(&__main);     //goto world of c++
}

__INLINE void function_goto(int (*pfunction)())
{
    __ASM __IO 
    (
        "mov r0,%0 \n\t"
        "bx r0     \n\t"
        ::"r"(pfunction)
    );
}



