#ifndef __PARAM_ROM_H_
#define __PARAM_ROM_H_

#include "Common.h"
#include <Wire.h>

#define AT24C_ADDR 0x50
#define ENLARGE_LEVEL 100		//100 = 1.0

class PARAM_ROM
{
private:
	u16 value;		// the true param value X ENLARGE_LEVEL
	u16 range;		// range of param 		X ENLARGE_LEVEL
	u16 addr;		// the addr for saving
public:
	/* 相关函数 */
	void WriteToEEPROM();
	void ReadFromEEPROM();
	void ClearTheData();

	/* 获取参数 */
	float GetParamFloatValue();
	float GetRangeFloatValue();
	u16 GetParamU16Value();
	u16 GetRangeU16Value();
	u16 GetAddr();

	/* 设置参数 */
	void SetParamValue(u16 valueIn);
	void SetRangeValue(u16 rangeIn);
	void SetAddr(u16 addrIn);
};
#endif