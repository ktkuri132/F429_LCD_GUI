#include <stm32f4xx.h>
#include <lib.h>

void EXTI_Configuration(void)
{
    // Enable SYSCFG clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    // Connect EXTI Line7 to PH7
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOH, EXTI_PinSource7);

    // Configure EXTI Line7
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line7;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; // Change this to the desired trigger type
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // Enable and set EXTI Line7 Interrupt to the lowest priority
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; // Change this to the appropriate IRQ channel
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F; // Change this to the desired preemption priority
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F; // Change this to the desired subpriority
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

uint8_t act_sign_1,act_sign_2;

void EXTI9_5_IRQHandler(void)
{
    // Check if EXTI_Line7 is asserted
    if (EXTI_GetITStatus(EXTI_Line7) != RESET)
    {
        tp_dev.scan(0);     //读坐标
        Button_check(&act_sign_1,0,360,250,100,50,"Enter");
        Button_check(&act_sign_2,1,520,250,100,50,"Esc");
        // Clear the EXTI line pending bit
        EXTI_ClearITPendingBit(EXTI_Line7);
    }
}