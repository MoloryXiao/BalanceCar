#ifndef __E2PROM_H_
#define __E2PROM_H_

#include "Common.h"
#include <Wire.h>

#define AT24C_ADDR 0x50

typedef struct
{
  float param;
  float range;
  u16 addr;
}PARAM_ROM;

void GetParamData(void);
void WriteShort(u16 addr,u16 data);
u16 ReadShort(u16 addr);
void WriteFloat(u16 addr,float data);
float ReadFloat(float addr);

#endif