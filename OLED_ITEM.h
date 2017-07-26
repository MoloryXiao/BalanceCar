#ifndef __OLED_ITEM_H
#define __OLED_ITEM_H	  

#include "Common.h"

class OLED_SPI
{
public:
	/* ���캯�� ��ʼ������ */
	OLED_SPI(u8 D0,u8 D1,u8 RES,u8 DC);
	
	/* ������Ա���� */		   		    
	void Init();					//����ģʽ��ʼ�� ��Ļ������ʼ��
	void WR_Byte(u8 dat,u8 cmd);	//����cmdֵ�������ݻ�����  
	void Display_On();				//����OLED��ʾ
	void Display_Off();				//�ر�OLED��ʾ
	void Clear();					//����
	void Set_Pos(u8 x,u8 y);		//��λ x:0~127 y:0~7

	/* ���ֻ��ֺ��� */
	//����һ���� x:0~63 y:0~7
	void Print_Point(u8 x, u8 y,u8 checkedState);
	//����һ���� ��(x,y)���Ҵ�ӡcount�����ص� count:0~63
	void Print_ALine(u8 x,u8 y,u8 count,u8 checkedState);
	//��ӡһ��Ӣ��'A' x:0~15 y:0~7
	void Print_AEN(u8 x, u8 y,u8 chr,u8 checkedState);	
	//��ӡһ��Ӣ��"ABCD" x:0~15 y:0~7 char *title,char *words
	void Print_ENString(u8 x,u8 y,const char *p,u8 checkedState,u8 middleState);	
	//��ӡһ������ x:0~15 y:0~3 len>=num.length
	void Print_Num(u8 x,u8 y,u32 num,u8 len,u8 checkedState,u8 middleState);
	//���д�ӡһ��������(С�������λ) x:0~15 y:0~3 num<655.35
	void Print_FloatNum(u8 x,u8 y,float num);	
	//����һ��ͼ
	void Draw_BMP(u8 x0, u8 y0,u8 x1, u8 y1,u8 BMP[]);			

	/* �������� */
	u16  pow(u8 m,u8 n);		//����m^n
	void Dele_Row(u8 row);		//ɾ��һ���� row(0~3)
	//void fun();

	/* ҳ�溯�� */
	void ENStr_Page(const char *words);
	void Comfirm_Page(const char *title,const char *words);
	void Switch_Page(const char *title,const char *words,unsigned char state,unsigned char clr);
	void Adjust_Page(const char *title,float param,float maxValue);

	/* ���ŵ�ƽ�仯���� */
	void OLED_CS_Set(u8 staus);	
	void OLED_RES_Set(u8 staus);
	void OLED_DC_Set(u8 staus);
	void OLED_SCL_Set(u8 staus);
	void OLED_SDA_Set(u8 staus);

private:
	u8 OLED_SCL;	//D0
	u8 OLED_SDA; 	//D1
	u8 OLED_RES;	//RES
	u8 OLED_DC;		//DC
	u8 OLED_CS;		//CS
};
#endif  
	 


