#include "lib.h"

void MY_NVIC_SetVectorTable(u32 NVIC_VectTab,u32 Offset)	 
{ 	   	  
	SCB->VTOR=NVIC_VectTab|(Offset&(u32)0xFFFFFE00);
}
		   
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group)	 
{ 
	u32 temp,temp1;	  
	temp1=(~NVIC_Group)&0x07;
	temp1<<=8;
	temp=SCB->AIRCR;  
	temp&=0X0000F8FF; 
	temp|=0X05FA0000; 
	temp|=temp1;	   
	SCB->AIRCR=temp; 	    	  				   
}

void GPIO_Set(GPIO_TypeDef* GPIOx,u32 BITx,u32 MODE,u32 OTYPE,u32 OSPEED,u32 PUPD)
{
    u32 pinpos=0,pos=0,curpin=0;
	for(pinpos=0;pinpos<16;pinpos++)
	{
		pos=1<<pinpos;	
		curpin=BITx&pos;
		if(curpin==pos)	
		{
			GPIOx->MODER&=~(3<<(pinpos*2));	
			GPIOx->MODER|=MODE<<(pinpos*2);	
			if((MODE==0X01)||(MODE==0X02))	
			{  
				GPIOx->OSPEEDR&=~(3<<(pinpos*2));	
				GPIOx->OSPEEDR|=(OSPEED<<(pinpos*2)); 
				GPIOx->OTYPER&=~(1<<pinpos) ;		
				GPIOx->OTYPER|=OTYPE<<pinpos;		
                GPIOx->PUPDR&=~(3<<(pinpos*2));	
                GPIOx->PUPDR|=PUPD<<(pinpos*2);	
		    }
	    }
    }
}


void GPIO_AF_Set(GPIO_TypeDef* GPIOx,u8 BITx,u8 AFx)
{  
	GPIOx->AFR[BITx>>3]&=~(0X0F<<((BITx&0X07)*4));
	GPIOx->AFR[BITx>>3]|=(u32)AFx<<((BITx&0X07)*4);
}  


void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)	 
{ 
	u32 temp;	  
	MY_NVIC_PriorityGroupConfig(NVIC_Group);
	temp=NVIC_PreemptionPriority<<(4-NVIC_Group);	  
	temp|=NVIC_SubPriority&(0x0f>>NVIC_Group);
	temp&=0xf;								
	NVIC->ISER[NVIC_Channel/32]|=1<<NVIC_Channel%32;
	NVIC->IP[NVIC_Channel]|=temp<<4;					    	  				   
}