#ifndef __COMMON_H
#define __COMMON_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

/* Fireduino 中 char为1字节 short为2字节 long为8字节 */
#define u8  unsigned char 	// 0~255
#define u16 unsigned short 	// 0~65535
#define u32 unsigned long	// 0~4294967295

#endif