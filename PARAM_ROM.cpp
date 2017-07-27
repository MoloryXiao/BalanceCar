#include "PARAM_ROM.h"

/* 相关函数 */
void PARAM_ROM::WriteToEEPROM()
{
	Wire.beginTransmission(AT24C_ADDR);
	Wire.write(this->addr>>8);
	Wire.write(this->addr);
	Wire.write(this->value>>8);
	Wire.write(this->value);
	Wire.endTransmission();
	delay(10);
}
void PARAM_ROM::ReadFromEEPROM()
{
	u16 data = 0;
	Wire.beginTransmission(AT24C_ADDR);
	Wire.write(this->addr>>8);
	Wire.write(this->addr);
	Wire.endTransmission();
	Wire.requestFrom(AT24C_ADDR,2);
	delay(10);
	if (Wire.available())
	{
	data = Wire.read();
	data = data<<8;
	data |= Wire.read();
	}
	this->value = data;
	delay(10);
}
void PARAM_ROM::ClearTheData()
{
	this->value = 0;
	WriteToEEPROM();
}

/* 获取参数 */
float PARAM_ROM::GetParamFloatValue()
{
	return this->value*1.0/ENLARGE_LEVEL;
}
float PARAM_ROM::GetRangeFloatValue()
{
	return this->range*1.0/ENLARGE_LEVEL;
}
u16 PARAM_ROM::GetParamU16Value()
{
	return this->value;
}
u16 PARAM_ROM::GetRangeU16Value()
{
	return this->range;
}
u16 PARAM_ROM::GetAddr()
{
	return this->addr;
}

/* 设置参数 */
void PARAM_ROM::SetParamValue(u16 valueIn)
{
	this->value = valueIn;
}
void PARAM_ROM::SetRangeValue(u16 rangeIn)
{
	this->range = rangeIn;
}
void PARAM_ROM::SetAddr(u16 addrIn)
{
	this->addr = addrIn;
}

