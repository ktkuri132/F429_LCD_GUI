#include "JY61_usart6.h"
#include "stdio.h"
#include "string.h"



typedef struct
{
	float angle[3];
}Angle;

struct SAngle//�Ƕ�
{
	short Angle[3];
	short T;
};
struct SAngle stcAngle;

typedef struct
{
	float gyro[3];
}Gyro;
struct SGyro//�Ǽ��ٶ�
{
	short Gyro[3];
	short T;
};
struct SGyro stcGyro;

typedef struct
{
	float acc[3];
}Acc;
struct SAcc//���ٶ�
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
	 
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)//�ж��ǲ���������жϷ���
	{   
		//USART_SendData(USART2,'a');
		//USART_SendData(USART1,USART_ReceiveData(USART1));//�ֽ����ݷ���ȥ(������֤)
		//Get_Jy61(USART_ReceiveData(USART2));
		//USART_ClearITPendingBit(USART2, USART_IT_RXNE); //�Ѿ�����������־λ 
	} 
	
}

/***********�ɼ�JY61P����**************/
void Get_Jy61(unsigned char Data)
{
	static unsigned char RX_BUFFER[250];
	static unsigned char ucRxCnt = 0;	
	RX_BUFFER[ucRxCnt++]=Data;	//���յ������ݴ��뻺������
	if (RX_BUFFER[0]!=0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
	{
		ucRxCnt=0;
		return;
	}
	if (ucRxCnt<11) {return;}//���ݲ���11�����򷵻�
	else
	{
	 switch(RX_BUFFER[1])//�ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
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
	 ucRxCnt=0;//��ջ�����
 }
}




