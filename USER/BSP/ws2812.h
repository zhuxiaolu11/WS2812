#ifndef __WS2812_H__
#define __WS2812_H__
#include "spi.h"

#ifdef __cplusplus
extern "C" {
#endif
void RGB_Set_Color(uint8_t ID,uint8_t color[3]);//单个LED颜色设置
void RGB_Reflash(uint8_t reflash_num);//SPI发送数据



void RGB_BLACK(uint8_t RGB_LEN);//全黑，可用于初始化
void RGB_RED(uint8_t RGB_LEN);  //全红
void RGB_GREEN(uint8_t RGB_LEN);//全绿
void RGB_BLUE(uint8_t RGB_LEN); //全蓝


//依次点亮成环
void ws2812_1(uint16_t RGB_LEN, uint8_t color[3]);
//单个LED循环转圈
void ws2812_2(uint16_t RGB_LEN, uint8_t color[3]);
//两个LED循环转圈
void ws2812_3(uint16_t RGB_LEN, uint8_t color[3]);
//渐变light=[0.12,8]  light通过比例来调节亮度
void ws2812_4(uint16_t RGB_LEN, int speed,float light);
//渐变循环light=[0.12,8]  light通过比例来调节亮度
void ws2812_5(uint16_t RGB_LEN, int speed,float light);
//三色亮度递减循环
void ws2812_6(uint16_t RGB_LEN, int speed);
//呼吸灯
void ws2812_7(uint16_t RGB_LEN, float light);
//整体渐变
void ws2812_8(uint16_t RGB_LEN, int speed,float light);
//闪烁
void ws2812_9(void);
#ifdef __cplusplus
}
#endif
#endif