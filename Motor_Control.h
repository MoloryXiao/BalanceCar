#ifndef MOTOR_CONTROL_H_
#define MOTOR_CONTROL_H_

#include "Arduino.h"

signed int  l=100;
signed int  r=-99;
unsigned char gdata[12];
unsigned char inByte;

void sndspeed(signed int left,signed int right)
{
   Serial1.print("s");
   Serial1.print(left);
   Serial1.print(",");
   Serial1.print(right);
   Serial1.print("e");   
}

#endif