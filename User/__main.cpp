#include "lib.h"
#include "gpio.h"




int __main()
{
    LCD_Clear(BLACK);
    POINT_COLOR=WHITE;
    
    
    while (1)
    {
        
        //LCD_ShowxNum(10,10,12,2,32,1);
        //LCD_ShowString(10,40,240,32,32,p);
        Printf(10,40,240,32,32,"hello,world");
        LCD_DrawRectangle(500,500,100,50);
        //LCD_Draw_Circle(500,300,100);
    }
    return 0;
}

