#include "ws2812.h"

#define 	LED_NUMS	112

#define CODE1	0xf0//1
#define CODE0   0xc0//0

uint8_t BLACK[3] = {0,0,0};
uint8_t RED[3] = {30,0,0};
uint8_t GREEN[3] = {0,30,0};
uint8_t BLUE[3] = {0,0,30};
uint8_t LED_BUFFER[24*LED_NUMS + 10];


extern SPI_HandleTypeDef hspi1;

//单个LED颜色设置
void RGB_Set_Color(uint8_t ID,uint8_t color[3])
{
    int i=0;
    for (i = 0; i < 8; i++) { //green
        LED_BUFFER[ID*24+i] = ((color[1] << i) & 0x80) ? CODE1 : CODE0;
    }
    for (i = 0; i < 8; i++) { //red
        LED_BUFFER[ID*24+8+i] = ((color[0] << i) & 0x80) ? CODE1 : CODE0;
    }
    for (i = 0; i < 8; i++) { //blue
        LED_BUFFER[ID*24+16+i] = ((color[2] << i) & 0x80) ? CODE1 : CODE0;
    }
}
//SPI发送
void RGB_Reflash(uint8_t reflash_num)
{
    HAL_SPI_Transmit_DMA(&hspi1, LED_BUFFER, 24*reflash_num);
}


//全部熄灭，可用于初始化
void RGB_BLACK(uint8_t RGB_LEN)
{
    for(int i=0;i<RGB_LEN;i++)
    {
        RGB_Set_Color(i,BLACK);
        RGB_Reflash(RGB_LEN);
    }
}
void RGB_RED(uint8_t RGB_LEN)
{
    for(int i=0;i<RGB_LEN;i++)
    {
        RGB_Set_Color(i,RED);
        RGB_Reflash(RGB_LEN);
    }
}
void RGB_GREEN(uint8_t RGB_LEN)
{
    for(int i=0;i<RGB_LEN;i++)
    {
        RGB_Set_Color(i,GREEN);
        RGB_Reflash(RGB_LEN);
    }
}
void RGB_BLUE(uint8_t RGB_LEN)
{
    for(int i=0;i<RGB_LEN;i++)
    {
        RGB_Set_Color(i,BLUE);
        RGB_Reflash(RGB_LEN);
    }
}


//依次点亮成环
void ws2812_1(uint16_t RGB_LEN,uint8_t color[3])
{
    for(int i=0;i<RGB_LEN;i++)
    {
        RGB_Set_Color(i,color);
        HAL_Delay (20); ///////////////////修改时间调整速度
        RGB_Reflash(RGB_LEN);
    }
}
//单个LED循环转圈
void ws2812_2(uint16_t RGB_LEN,uint8_t color[3])
{
    for(int i=0;i<RGB_LEN;i++)
    {
        RGB_Set_Color(i,color);
        RGB_Reflash(RGB_LEN);
        HAL_Delay (30);
        RGB_BLACK(112);//////熄灭所有LED
        RGB_Reflash(RGB_LEN);
        HAL_Delay (30);
    }
}
//两个LED循环转圈
void ws2812_3(uint16_t RGB_LEN ,uint8_t color[3])
{
    for(int i=0;i<RGB_LEN-1;i++)
    {
        RGB_Set_Color(i,color);
        RGB_Set_Color(i+1,color);
        RGB_Reflash(RGB_LEN);
        HAL_Delay (20);
        RGB_BLACK(112);//////熄灭所有LED
        RGB_Reflash(RGB_LEN);
        HAL_Delay (10);
    }
}
//渐变light=[0.12,8]  light通过比例来调节亮度
void ws2812_4(uint16_t RGB_LEN,int speed,float light)
{
    if(light==0)
        light=1;
    for(int j=0;j<12;j++)//A
    {
        uint8_t My_color[3]={32/light ,3*j/light  ,  0};
        RGB_Set_Color(j,My_color);
    }

    for(int j=12;j<20;j++)//B
    {
        uint8_t My_color[3]={(32-4*(j-12))/light ,32/light  ,  0};
        RGB_Set_Color(j,My_color);
    }

    for(int j=20;j<28;j++)//C
    {
        uint8_t My_color[3]={0 ,32/light  ,  4*(j-20)/light};
        RGB_Set_Color(j,My_color);
    }

    for(int j=28;j<36;j++)//D
    {
        uint8_t My_color[3]={0 ,(32-4*(j-28))/light  ,  32/light};
        RGB_Set_Color(j,My_color);
    }

    for(int j=36;j<46;j++)//E
    {
        uint8_t My_color[3]={3*(j-36)/light ,0  ,  30/light};
        RGB_Set_Color(j,My_color);
    }

    for(int j=46;j<56;j++)//F
    {
        uint8_t My_color[3]={30/light ,0  ,  30-3*(j-46)/light};
        RGB_Set_Color(j,My_color);
    }
    uint8_t My_color[3]={ 0 ,30/light  , 0 };
    RGB_Set_Color(56,My_color);
#if 1
////////////////////
    for(int j=0+56;j<12+56;j++)//A
    {
        uint8_t My_color[3]={32/light ,3*(j-56)/light  ,  0};
        RGB_Set_Color(j,My_color);
    }

    for(int j=12+56;j<20+56;j++)//B
    {
        uint8_t My_color[3]={(32-4*(j-12-56))/light ,32/light  ,  0};
        RGB_Set_Color(j,My_color);
    }

    for(int j=20+56;j<28+56;j++)//C
    {
        uint8_t My_color[3]={0 ,32/light  ,  4*(j-20-56)/light};
        RGB_Set_Color(j,My_color);
    }

    for(int j=28+56;j<36+56;j++)//D
    {
        uint8_t My_color[3]={0 ,(32-4*(j-28-56))/light  ,  32/light};
        RGB_Set_Color(j,My_color);
    }

    for(int j=36+56;j<46+56;j++)//E
    {
        uint8_t My_color[3]={3*(j-36-56)/light ,0  ,  30/light};
        RGB_Set_Color(j,My_color);
    }

    for(int j=46+56;j<56+56;j++)//F
    {
        uint8_t My_color[3]={30/light ,0  ,  (30-3*(j-46-56))/light};
        RGB_Set_Color(j,My_color);
    }
#endif
    RGB_Reflash(RGB_LEN);
    HAL_Delay (speed);
}
//渐变循环light=[0.12,8]  light通过比例来调节亮度
void ws2812_5(uint16_t RGB_LEN,int speed,float light)
{
    for(int i=0;i<56;i++)
    {
        for(int j=0;j<12;j++)//A
        {
            uint8_t My_color[3]={32/light ,3*j/light  ,  0};
            if(i+j>=56)
            {
                RGB_Set_Color(j+i-56,My_color);
            }
            else
            {
                RGB_Set_Color(j+i,My_color);
            }
            RGB_Reflash(RGB_LEN);
        }
        for(int j=12;j<20;j++)//B
        {
            uint8_t My_color[3]={(32-4*(j-12))/light ,32/light  ,  0};
            if(i+j>=56)
            {
                RGB_Set_Color(j+i-56,My_color);
            }
            else
            {
                RGB_Set_Color(j+i,My_color);
            }
            RGB_Reflash(RGB_LEN);
        }
        for(int j=20;j<28;j++)//C
        {
            uint8_t My_color[3]={0 ,32/light  ,  4*(j-20)/light};
            if(i+j>=56)
            {
                RGB_Set_Color(j+i-56,My_color);
            }
            else
            {
                RGB_Set_Color(j+i,My_color);
            }
            RGB_Reflash(RGB_LEN);
        }
        for(int j=28;j<36;j++)//D
        {
            uint8_t My_color[3]={0 ,(32-4*(j-28))/light  ,  32/light};
            if(i+j>=56)
            {
                RGB_Set_Color(j+i-56,My_color);
            }
            else
            {
                RGB_Set_Color(j+i,My_color);
            }
            RGB_Reflash(RGB_LEN);
        }
        for(int j=36;j<46;j++)//E
        {
            uint8_t My_color[3]={3*(j-36)/light ,0  ,  30/light};
            if(i+j>=56)
            {
                RGB_Set_Color(j+i-56,My_color);
            }
            else
            {
                RGB_Set_Color(j+i,My_color);
            }
            RGB_Reflash(RGB_LEN);
        }
        for(int j=46;j<56;j++)
        {
            uint8_t My_color[3]={30/light ,0  ,  (30-3*(j-46))/light};
            if(i+j>=56)
            {
                RGB_Set_Color(j+i-56,My_color);
            }
            else
            {
                RGB_Set_Color(j+i,My_color);
            }
            RGB_Reflash(RGB_LEN);
        }
/////////////////////////////////////////////////////////////////////
        for(int j=0;j<12;j++)//A
        {
            uint8_t My_color[3]={32/light ,3*j/light  ,  0};
            if(i+j+56>=112)
            {
                RGB_Set_Color(j+i-56+56,My_color);
            }
            else
            {
                RGB_Set_Color(j+i+56,My_color);
            }
            RGB_Reflash(RGB_LEN);
        }
        for(int j=12;j<20;j++)//B
        {
            uint8_t My_color[3]={(32-4*(j-12))/light ,32/light  ,  0};
            if(i+j+56>=112)
            {
                RGB_Set_Color(j+i-56+56,My_color);
            }
            else
            {
                RGB_Set_Color(j+i+56,My_color);
            }
            RGB_Reflash(RGB_LEN);
        }
        for(int j=20;j<28;j++)//C
        {
            uint8_t My_color[3]={0 ,32/light  ,  4*(j-20)/light};
            if(i+j+56>=112)
            {
                RGB_Set_Color(j+i-56+56,My_color);
            }
            else
            {
                RGB_Set_Color(j+i+56,My_color);
            }
            RGB_Reflash(RGB_LEN);
        }
        for(int j=28;j<36;j++)//D
        {
            uint8_t My_color[3]={0 ,(32-4*(j-28))/light  ,  32/light};
            if(i+j+56>=112)
            {
                RGB_Set_Color(j+i-56+56,My_color);
            }
            else
            {
                RGB_Set_Color(j+i+56,My_color);
            }
            RGB_Reflash(RGB_LEN);
        }
        for(int j=36;j<46;j++)//E
        {
            uint8_t My_color[3]={3*(j-36)/light ,0  ,  30/light};
            if(i+j+56>=112)
            {
                RGB_Set_Color(j+i-56+56,My_color);
            }
            else
            {
                RGB_Set_Color(j+i+56,My_color);
            }
            RGB_Reflash(RGB_LEN);
        }
        for(int j=46;j<56;j++)
        {
            uint8_t My_color[3]={30/light ,0  ,  (30-3*(j-46))/light};
            if(i+j+56>=112)
            {
                RGB_Set_Color(j+i-56+56,My_color);
            }
            else
            {
                RGB_Set_Color(j+i+56,My_color);
            }
            RGB_Reflash(RGB_LEN);
        }
        RGB_Reflash(RGB_LEN);
        HAL_Delay (speed);
    }
}
//三色亮度递减循环
void ws2812_6(uint16_t RGB_LEN,int speed)
{
    for(int i=0;i<56;i++)
    {
        for(int j=0;j<18;j++)//A
        {
            uint8_t My_color[3]={3*j,0  ,  0};
            if(i+j>=56)
            {
                RGB_Set_Color(j+i-56,My_color);
            }
            else
            {
                RGB_Set_Color(j+i,My_color);
            }
        }
        for(int j=18;j<36;j++)//B
        {
            uint8_t My_color[3]={0,3*(j-18)   ,  0};
            if(i+j>=56)
            {
                RGB_Set_Color(j+i-56,My_color);
            }
            else
            {
                RGB_Set_Color(j+i,My_color);
            }
        }
        for(int j=36;j<56;j++)//C
        {
            uint8_t My_color[3]={0 ,0  ,  3*(j-36)};
            if(i+j>=56)
            {
                RGB_Set_Color(j+i-56,My_color);
            }
            else
            {
                RGB_Set_Color(j+i,My_color);
            }
        }

        for(int j=0;j<18;j++)//A
        {
            uint8_t My_color[3]={3*j,0  ,  0};
            if(i+j+56>=112)
            {
                RGB_Set_Color(j+i-56+56,My_color);
            }
            else
            {
                RGB_Set_Color(j+i+56,My_color);
            }
        }
        for(int j=18;j<36;j++)//B
        {
            uint8_t My_color[3]={0,3*(j-18)   ,  0};
            if(i+j+56>=112)
            {
                RGB_Set_Color(j+i-56+56,My_color);
            }
            else
            {
                RGB_Set_Color(j+i+56,My_color);
            }
        }
        for(int j=36;j<56;j++)//C
        {
            uint8_t My_color[3]={0 ,0  ,  3*(j-36)};
            if(i+j+56>=112)
            {
                RGB_Set_Color(j+i-56+56,My_color);
            }
            else
            {
                RGB_Set_Color(j+i+56,My_color);
            }
        }
        HAL_Delay (speed);
        RGB_Reflash(RGB_LEN);
    }

}
//呼吸灯
void ws2812_7(uint16_t RGB_LEN ,float light)
{
    for(int i=0;i<light;i++)
    {
        for(int j=0;j<RGB_LEN;j++)//B
        {
            uint8_t My_color[3]={0,0 ,i};
            RGB_Set_Color(j,My_color);
        }
        RGB_Reflash(RGB_LEN);
        HAL_Delay(60);
    }
    for(int i=0;i<light;i++)
    {
        for(int j=0;j<RGB_LEN;j++)//B
        {
            uint8_t My_color[3]={0,0 ,light-i};
            RGB_Set_Color(j,My_color);
        }
        RGB_Reflash(RGB_LEN);
        HAL_Delay(50);
    }

}
//整体渐变
void ws2812_8(uint16_t RGB_LEN, int speed,float light)
{

    for(int j=0;j<12;j++)//A
    {
        for(int i=0;i<RGB_LEN;i++)
        {
            uint8_t My_color[3]={32/light,3*j/light  ,  0};
            RGB_Set_Color(i,My_color);
        }
        RGB_Reflash(RGB_LEN);
        HAL_Delay (speed);
    }
    for(int j=12;j<20;j++)//B
    {
        for(int i=0;i<RGB_LEN;i++)
        {
            uint8_t My_color[3]={(32-4*(j-12))/light,32/light  ,  0};
            RGB_Set_Color(i,My_color);
        }
        RGB_Reflash(RGB_LEN);
        HAL_Delay (speed);
    }
    for(int j=20;j<28;j++)//C
    {
        for(int i=0;i<RGB_LEN;i++)
        {
            uint8_t My_color[3] = {0, 32/light, 4 * (j - 20)/light};
            RGB_Set_Color(i, My_color);
        }
        RGB_Reflash(RGB_LEN);
        HAL_Delay (speed);
    }
    for(int j=28;j<36;j++)//D
    {
        for(int i=0;i<RGB_LEN;i++)
        {
            uint8_t My_color[3]= {0, (32 - 4 * (j - 28))/light, 32/light};
            RGB_Set_Color(i, My_color);
        }
        RGB_Reflash(RGB_LEN);
        HAL_Delay (speed);
    }
    for(int j=36;j<46;j++)//E
    {
        for(int i=0;i<RGB_LEN;i++)
        {
            uint8_t My_color[3] = {3 * (j - 36)/light, 0, 30/light};
            RGB_Set_Color(i, My_color);
        }
        RGB_Reflash(RGB_LEN);
        HAL_Delay (speed);
    }
    for(int j=46;j<56;j++)
    {
        for(int i=0;i<RGB_LEN;i++)
        {
            uint8_t My_color[3] = {30/light, 0, (30 - 3 * (j - 46))/light};
            RGB_Set_Color(i, My_color);
        }
        RGB_Reflash(RGB_LEN);
        HAL_Delay (speed);
    }

}
//闪烁
void ws2812_9(void)
{
    RGB_RED(112);
    HAL_Delay(500);
    RGB_GREEN(112);
    HAL_Delay(500);
    RGB_BLUE(112);
    HAL_Delay(500);
}