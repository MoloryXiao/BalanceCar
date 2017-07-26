/*
* Copyright (c) 2017, 电子科技大学中山学院
* ALL rights reserved
*
*文件名称: E2prom.cpp
*文本标识：
*摘    要：实现向32K EEPROM的存取
*
*当前版本：
*作    者：萧沐磊
*完成日期：2017-07-10
*
*取代版本号：
*作    者：萧沐磊
*版本描述：
*/
#include "E2prom.h"

PARAM_ROM V_P_Param;
PARAM_ROM V_I_Param;
PARAM_ROM D_P_Param;
PARAM_ROM D_D_Param;
PARAM_ROM A_P_Param;
PARAM_ROM A_D_Param;

/****************************************************************************
* 名    称：WriteShort()
* 功    能：向EEPROM写入两个字节的数据
* 入口参数：addr:地址块 data:写入的数据
* 出口参数：无
****************************************************************************/
void WriteShort(u16 addr,u16 data)
{
  Wire.beginTransmission(AT24C_ADDR);
  Wire.write(addr>>8);
  Wire.write(addr);
  Wire.write(data>>8);
  Wire.write(data);
  Wire.endTransmission();
  delay(10);
}

/****************************************************************************
* 名    称：ReadShort()
* 功    能：从EEPROM指定地址读取两个字节的数据
* 入口参数：addr:地址块
* 出口参数：16位的数据
****************************************************************************/
u16 ReadShort(u16 addr)
{
  u16 data;
  Wire.beginTransmission(AT24C_ADDR);
  Wire.write(addr>>8);
  Wire.write(addr);
  Wire.endTransmission();
  Wire.requestFrom(AT24C_ADDR,2);
  delay(10);
  if (Wire.available())
  {
    data = Wire.read();
    data = data<<8;
    data |= Wire.read();
  }
  delay(10);
  return data;
}

/****************************************************************************
* 名    称：WriteFloat()
* 功    能：向EEPROM写入4个字节的数据
* 入口参数：addr:地址块 data:写入的数据
* 出口参数：无
****************************************************************************/
void WriteFloat(u16 addr,float data)
{
  
}

/****************************************************************************
* 名    称：ReadFloat()
* 功    能：从EEPROM指定地址读取4个字节的数据
* 入口参数：addr:地址块
* 出口参数：16位的数据
****************************************************************************/
float ReadFloat(u16 addr)
{
  
}

/****************************************************************************
* 名    称：GetParamData()
* 功    能：从EEPROM中获取到速度、方向、角度的PID值
* 入口参数：无
* 出口参数：无
****************************************************************************/
void GetParamData(void)
{
  //V_P_Param.param = 12;
  V_P_Param.range = 10;
  V_P_Param.addr  = 0x0040;
  V_P_Param.param = ReadShort(V_P_Param.addr)*1.0/100;

  //V_I_Param.param = 10;
  V_I_Param.range = 10;
  V_I_Param.addr  = 0x0044;
  V_I_Param.param = ReadShort(V_I_Param.addr)*1.0/100;

  //D_P_Param.param = 10;
  D_P_Param.range = 10;
  D_P_Param.addr  = 0x0048;
  D_P_Param.param = ReadShort(D_P_Param.addr)*1.0/100;

  //D_D_Param.param = 20;
  D_D_Param.range = 10;
  D_D_Param.addr  = 0x004C;
  D_D_Param.param = ReadShort(D_D_Param.addr)*1.0/100;

  //A_P_Param.param = 13;
  A_P_Param.range = 10;
  A_P_Param.addr  = 0x0050;
  A_P_Param.param = ReadShort(A_P_Param.addr)*1.0/100;

  //A_D_Param.param = 40;
  A_D_Param.range = 5;
  A_D_Param.addr  = 0x0054;
  A_D_Param.param = ReadShort(A_D_Param.addr)*1.0/100;
}
