#ifndef __WS2812_H__
#define __WS2812_H__
#include "spi.h"

#ifdef __cplusplus
extern "C" {
#endif
void RGB_Set_Color(uint8_t ID,uint8_t color[3]);//����LED��ɫ����
void RGB_Reflash(uint8_t reflash_num);//SPI��������



void RGB_BLACK(uint8_t RGB_LEN);//ȫ�ڣ������ڳ�ʼ��
void RGB_RED(uint8_t RGB_LEN);  //ȫ��
void RGB_GREEN(uint8_t RGB_LEN);//ȫ��
void RGB_BLUE(uint8_t RGB_LEN); //ȫ��


//���ε����ɻ�
void ws2812_1(uint16_t RGB_LEN, uint8_t color[3]);
//����LEDѭ��תȦ
void ws2812_2(uint16_t RGB_LEN, uint8_t color[3]);
//����LEDѭ��תȦ
void ws2812_3(uint16_t RGB_LEN, uint8_t color[3]);
//����light=[0.12,8]  lightͨ����������������
void ws2812_4(uint16_t RGB_LEN, int speed,float light);
//����ѭ��light=[0.12,8]  lightͨ����������������
void ws2812_5(uint16_t RGB_LEN, int speed,float light);
//��ɫ���ȵݼ�ѭ��
void ws2812_6(uint16_t RGB_LEN, int speed);
//������
void ws2812_7(uint16_t RGB_LEN, float light);
//���彥��
void ws2812_8(uint16_t RGB_LEN, int speed,float light);
//��˸
void ws2812_9(void);
#ifdef __cplusplus
}
#endif
#endif