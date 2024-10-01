#include "JY61_usart6.h"
#include "stdio.h"
#include "string.h"



typedef struct
{
	float angle[3];
}Angle;

struct SAngle//角度
{
	short Angle[3];
	short T;
};
struct SAngle stcAngle;

typedef struct
{
	float gyro[3];
}Gyro;
struct SGyro//角加速度
{
	short Gyro[3];
	short T;
};
struct SGyro stcGyro;

typedef struct
{
	float acc[3];
}Acc;
struct SAcc//加速度
{
	short Acc[3];
	short T;
};
struct SAcc stcAcc;

float Angle_S[3];
float Gyro_S[3];
float Acc_S[3];

/*
void USART2_IRQHandler(void)
{
	 
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)//判断是不是真的有中断发生
	{   
		//USART_SendData(USART2,'a');
		//USART_SendData(USART1,USART_ReceiveData(USART1));//又将数据发回去(用于验证)
		//Get_Jy61(USART_ReceiveData(USART2));
		//USART_ClearITPendingBit(USART2, USART_IT_RXNE); //已经处理就清楚标志位 
	} 
	
}

/***********采集JY61P数据**************/
void Get_Jy61(unsigned char Data)
{
	static unsigned char RX_BUFFER[250];
	static unsigned char ucRxCnt = 0;	
	RX_BUFFER[ucRxCnt++]=Data;	//将收到的数据存入缓冲区中
	if (RX_BUFFER[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}//数据不满11个，则返回
	else
	{
	 switch(RX_BUFFER[1])//判断数据是哪种数据，然后将其拷贝到对应的结构体中，有些数据包需要通过上位机打开对应的输出后，才能接收到这个数据包的数据
	 {
			case 0x51:
						memcpy(&stcAcc,&RX_BUFFER[2],8);
						for(uint8_t j = 0; j < 3; j++)
							{
								Acc_S[j] = (float)stcAcc.Acc[j]/32768*16;
							}
						break;
		  case 0x52:
						memcpy(&stcGyro,&RX_BUFFER[2],8);
						for(uint8_t j = 0; j < 3; j++)
							{
								Gyro_S[j] = (float)stcGyro.Gyro[j]/32768*2000;
							}
						break;
	    case 0x53:
						memcpy(&stcAngle,&RX_BUFFER[2],8);
						for(uint8_t j = 0; j < 3; j++)
							{
								Angle_S[j] = (float)stcAngle.Angle[j]/32768*180;
							}		 
						break;
	 }
	 ucRxCnt=0;//清空缓存区
 }
}




