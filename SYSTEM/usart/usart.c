#include "sys.h"
#include "usart.h"	 

int16_t RX_sign;

#include <stdarg.h>

//定义keil宏，在MDK编译环境下支持printf等函数

	#if 1
		#ifdef  __CC_ARM
			#pragma import(__use_no_semihosting)
			struct __FILE 
			{ 
				int handle; 
			}; 
			#elif defined ( __GNUC__ ) || defined (__clang__)
			__asm (".global __use_no_semihosting\n\t");   
		#endif
	#endif


/*arm-gcc编译环境下实现printf函数的重定向  失败*/
/*printf函数的替代品*/
#ifdef __GNUC__
void printf(char *format, ...)
{
	char String[256];						//定义字符数组
	va_list arg;							//定义可变参数列表数据类型的变量arg
	va_start(arg, format);					//从format开始，接收参数列表到arg变量
	vsprintf(String, format, arg);			//使用vsprintf打印格式化字符串和参数列表到字符数组中
	va_end(arg);							//结束变量arg
	u8 size;
	for(size=0;String[size]!='\0';size++)
	{
		USART1_SEND_DATA_U8(String[size]);
	}
	
}


#endif

 
#if EN_USART1_RX   
  	
u8 USART_RX_BUF[USART_REC_LEN];     

u16 USART_RX_STA=0;         

int i=0;

void uart_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);
	mantissa=temp;				 
	fraction=(temp-mantissa)*16; 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->AHB1ENR|=1<<0;   	
	RCC->APB2ENR|=1<<4;  	 
	GPIO_Set(GPIOA,1<<9|1<<10,2,0,2,1);
 	GPIO_AF_Set(GPIOA,9,7);	
	GPIO_AF_Set(GPIOA,10,7); 	   

 	USART1->BRR=mantissa; 		 
	USART1->CR1&=~(1<<15); 	
	USART1->CR1|=1<<3;  	
#if EN_USART1_RX		  	

	USART1->CR1|=1<<2;  	
	USART1->CR1|=1<<5;    		    	
	MY_NVIC_Init(3,3,USART1_IRQn,2);
#endif
	USART1->CR1|=1<<13;  	
}

//串口中断
void USART1_IRQHandler(void)
{
	u8 res;	
	if(USART1->SR&(1<<5))
	{	 
		res=USART1->DR; 
		if((USART_RX_STA&0x8000)==0)
		{
			if(USART_RX_STA&0x4000)
			{
				if(res!=0x0a)USART_RX_STA=0;
				else USART_RX_STA|=0x8000;	
			}
			else 
			{	
				if(res==0x0d)USART_RX_STA|=0x4000;
				else
				{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=res;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;	  
				}		 
			}
		}  		 									     
	} 

}

//发送函数
void USART1_SEND_DATA_U8(u8 data)
{
	USART1->DR = (data & (uint16_t)0x01FF);
	while((USART1->SR&0X40)==0);
}

void USART1_SEND_BUF_U8(u8*buf,u8 len)
{
	while(len)
	{
		USART1_SEND_DATA_U8(*buf);
		buf++;
		len--;
	}
}































#endif

