//#define STM32F40_41xxx

#include <stm32f4xx.h>
#include <touch.h>
#include <JY61_usart6.h>

extern float Angle_S[3];

int main()
{
    BSP_Init();
    
    // 使用 “按钮”必须在 外部中断的函数中调用

    
    while(1)
    {    
        //Printf(0,0,240,32,32,0,"x:%d,y:%d",tp_dev.x[0],tp_dev.y[0]);
        //printf("%d,%d\r\n",tp_dev.x[0],tp_dev.y[0]);
    }
}

int a;

void button_response(uint8_t *act_sign)
{
    switch (*act_sign)
    {
        case 0:
        {
            a +=2;
            Printf(0,64,240,32,32,0,"a:%d",a); 
            printf("%d\r\n",a);
        }   
        break;
        
        case 1:
        {
            a--;
            Printf(0,64,240,32,32,0,"a:%d",a); 
            printf("%d\r\n",a);
        }
        break;
        default:
            break;
    }

}
