#ifndef __MENU_H
#define __MENU_H

#include "Common.h"
#include "OLED_ITEM.h"
#include "KeyScanner.h"
#include "E2prom.h"

#define MAXROW 8        //选项总数
#define MINROW 1

// 选项结构体
typedef struct
{
  char content[17];
}Menu_Item;

const Menu_Item EN_Menu[]=
{
  {"PARAM MENU"},
  {"START EX"},
  {"Get The Angle"},
  {"Vel P Value"},
  {"Vel I Value"},
  {"Dir P Value"},
  {"Dir D Value"},
  {"Angle P Value"},
  {"Angle D Value"},
};

void OLED_FirstPrint(OLED_SPI &MyOLED);
void OLED_ReturnPrint(OLED_SPI &MyOLED);
void AdjParamFunc(OLED_SPI &MyOLED,PARAM_ROM &par,const char* title);
void ComfrimFunc(OLED_SPI &MyOLED,u8 &flag,const char *title,const char *print);
void SecondLevelMenu(OLED_SPI &MyOLED);
void FirstLevelMenu(OLED_SPI &MyOLED);

#endif
