#ifndef __GUILIB__
#define __GUILIB__


#ifdef __cplusplus
extern "C"
{
#endif

#include "lib.h"
void Button_check(uint8_t *act_sign,uint8_t button_num,uint16_t x,uint16_t y,uint16_t w,uint16_t h,char *string);
__attribute__((weak)) __INLINE void button_response(uint8_t *act_sign) ;       /* 按键槽函数  */


void obj_move();


#ifdef __cplusplus
}
#endif

#endif