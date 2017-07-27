#include "EEPROM.h"

PARAM_ROM V_P_Param;
PARAM_ROM V_I_Param;
PARAM_ROM D_P_Param;
PARAM_ROM D_D_Param;
PARAM_ROM A_P_Param;
PARAM_ROM A_D_Param;


/****************************************************************************
* 名    称：GetParamData()
* 功    能：从EEPROM中获取到速度、方向、角度的PID值
* 入口参数：无
* 出口参数：无
****************************************************************************/

void GetParamData(void)
{
  V_P_Param.SetRangeValue(10*ENLARGE_LEVEL);
  V_P_Param.SetAddr(0x0040);
  V_P_Param.ReadFromEEPROM();

  V_I_Param.SetRangeValue(10*ENLARGE_LEVEL);
  V_I_Param.SetAddr(0x0044);
  V_I_Param.ReadFromEEPROM();

  D_P_Param.SetRangeValue(10*ENLARGE_LEVEL);
  D_P_Param.SetAddr(0x0048);
  D_P_Param.ReadFromEEPROM();

  D_D_Param.SetRangeValue(10*ENLARGE_LEVEL);
  D_D_Param.SetAddr(0x004C);
  D_D_Param.ReadFromEEPROM();

  A_P_Param.SetRangeValue(10*ENLARGE_LEVEL);
  A_P_Param.SetAddr(0x0050);
  A_P_Param.ReadFromEEPROM();

  A_D_Param.SetRangeValue(5*ENLARGE_LEVEL);
  A_D_Param.SetAddr(0x0054);
  A_D_Param.ReadFromEEPROM();
}

/****************************************************************************
* 名    称：ClearParamData()
* 功    能：参数值清零
* 入口参数：无
* 出口参数：无
****************************************************************************/
void ClearParamData(void)
{
  V_P_Param.ClearTheData(); V_I_Param.ClearTheData();
  D_P_Param.ClearTheData(); D_D_Param.ClearTheData();
  A_P_Param.ClearTheData(); A_D_Param.ClearTheData();
}