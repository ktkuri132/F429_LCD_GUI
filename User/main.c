#include "stm32f4xx.h"
#include "sys.h"
#include "delay.h"
#include "lib.h"
#include "usart.h"
#include "gt9xxx.h"
#include "touch.h"
#include "GUILib.h"

int a;

int system_init(void)
{
    delay_init(180);
    uart_init(90,115200);
    SDRAM_Init();
    LCD_Init();
    gt9xxx_init();
    
    uint8_t act_sign_1,act_sign_2;

    LCD_DrawRectangle(360,250,100,50);
    LCD_DrawRectangle(520,250,100,50);
    
    uint16_t x,y;
    while(1)
    {
        
        
        tp_dev.scan(0);
        
        Button_check(&act_sign_1,0,360,250,100,50,"Enter");
        Button_check(&act_sign_2,1,520,250,100,50,"Esc");
        //obj_move();
        Printf(0,0,240,32,32,0,"x:%d,y:%d",tp_dev.x[0],tp_dev.y[0]);
        
    }
    
    function_goto(&__main);     //goto world of c++
}

void button_response(uint8_t *act_sign)
{
    switch (*act_sign)
    {
        case 0:
        {
            a++;
            Printf(0,32,240,32,32,0,"a:%d",a); 
        }   
        break;
        
        case 1:
        {
            a--;
            Printf(0,32,240,32,32,0,"a:%d",a); 
        }
        break;
        default:
            break;
    }
    
        
    
    

}



