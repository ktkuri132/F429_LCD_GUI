#include "sys.h"

void WFI_SET(void)
{
    __ASM volatile("WFI");
}

void INTX_DISABLE(void)
{
	__ASM volatile("CPSID   I");
	__ASM volatile("BX      LR");  
}

void INTX_ENABLE(void)
{
	__ASM volatile("CPSIE   I");
	__ASM volatile("BX      LR");
}

void MSR_MSP(u32 addr) 
{
	__ASM volatile("MSR MSP, r0"); 			//set Main Stack value
	__ASM volatile("BX r14");
}






















