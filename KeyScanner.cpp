/*
* Copyright (c) 2017, 电子科技大学中山学院
* ALL rights reserved
*
*文件名称: KeyScanner.cpp
*文本标识：
*摘    要：对OLED的四个按键进行扫描
*
*当前版本：
*作    者：萧沐磊
*完成日期：2017-07-10
*
*取代版本号：
*作    者：萧沐磊
*版本描述：
*/
#include "KeyScanner.h"

/****************************************************************************
* 名    称：InitKeys()
* 功    能：初始化四个按键
* 入口参数：无
* 出口参数：无
****************************************************************************/
void InitKeys(void)
{
  pinMode(BUTTON_DOWN_PIN,INPUT);
  pinMode(BUTTON_UP_PIN,INPUT);
  pinMode(BUTTON_OK_PIN,INPUT);
  pinMode(BUTTON_CANCEL_PIN,INPUT);
  digitalWrite(BUTTON_DOWN_PIN,HIGH);
  digitalWrite(BUTTON_UP_PIN,HIGH);
  digitalWrite(BUTTON_OK_PIN,HIGH);
  digitalWrite(BUTTON_CANCEL_PIN,HIGH);
}
/****************************************************************************
* 名    称：DownKeyState()
* 功    能：在可以Down的前提下 扫描Down按键的情况 消抖后获取按键状态
* 入口参数：无
* 出口参数：true：Down按键按下， false：Down按键没有按下
****************************************************************************/
bool DownKeyState(void)
{
  if(digitalRead(BUTTON_DOWN_PIN)==0) 
  {
    delay(SHAKE_DELAY_1);
    if(digitalRead(BUTTON_DOWN_PIN)==0) return true;
    else return false;
  }
  return false;
}

/****************************************************************************
* 名    称：DownKeyState2()
* 功    能：在可以Down的前提下 扫描Down按键的情况 消抖后获取按键状态 
*           较前一个函数的延时时间要短 意味着读取按键状态个数变多
* 入口参数：无
* 出口参数：true：Down按键按下， false：Down按键没有按下
****************************************************************************/
bool DownKeyState2(void)
{
  if(digitalRead(BUTTON_DOWN_PIN)==0) 
  {
    delay(SHAKE_DELAY_2);
    if(digitalRead(BUTTON_DOWN_PIN)==0) return true;
    else return false;
  }
  return false;
}

/****************************************************************************
* 名    称：UpKeyState()
* 功    能：在可以Up的情况下 扫描Up按键的情况 消抖后获取按键状态
* 入口参数：无
* 出口参数：true：Up按键按下， false：Up按键没有按下
****************************************************************************/
bool UpKeyState(void)
{
  if(digitalRead(BUTTON_UP_PIN)==0)
  {
    delay(SHAKE_DELAY_1);
    if(digitalRead(BUTTON_UP_PIN)==0) return true;
    else return false;
  }
  return false;
}

/****************************************************************************
* 名    称：UpKeyState2()
* 功    能：在可以Up的情况下 扫描Up按键的情况 消抖后获取按键状态 
*           较前一个函数的延时时间要短 意味着读取按键状态个数变多
* 入口参数：无
* 出口参数：true：Up按键按下， false：Up按键没有按下
****************************************************************************/
bool UpKeyState2(void)
{
  if(digitalRead(BUTTON_UP_PIN)==0)
  {
    delay(SHAKE_DELAY_2);
    if(digitalRead(BUTTON_UP_PIN)==0) return true;
    else return false;
  }
  return false;
}

/****************************************************************************
* 名    称：EnterKeyState()
* 功    能：扫描Enter按键的情况 消抖后获取按键状态 
* 入口参数：无
* 出口参数：true：Enter按键按下， false：Enter按键没有按下
****************************************************************************/
bool EnterKeyState(void)
{
  if(digitalRead(BUTTON_OK_PIN)==0)
  {
    delay(SHAKE_DELAY_1);
    if(digitalRead(BUTTON_OK_PIN)==0) return true;
    else return false;
  }else return false;
}

/****************************************************************************
* 名    称：CancelKeyState()
* 功    能：扫描Cancel按键的情况 消抖后获取按键状态 
* 入口参数：无
* 出口参数：true：Cancel按键按下， false：Cancel按键没有按下
****************************************************************************/
bool CancelKeyState(void)
{
  if(digitalRead(BUTTON_CANCEL_PIN)==0)
  {
    delay(SHAKE_DELAY_1);
    if(digitalRead(BUTTON_CANCEL_PIN)==0) return true;
    else return false;
  }else return false;
}

/****************************************************************************
* 名    称：EnterOrCancel()
* 功    能：扫描Enter按键和Cancel按键的状态
* 入口参数：无
* 出口参数：true：Enter按键按下， false：Cancel按键按下
****************************************************************************/
bool EnterOrCancel(void)
{
  while(1)
  {
    if(EnterKeyState())
    {
      return 1;
    }
    if(CancelKeyState())
    {
      return 0;
    }
  }
}
