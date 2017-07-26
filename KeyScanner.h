#ifndef __KEYSCANNER_H__
#define __KEYSCANNER_H__

#include "Common.h"

/* 按键端口号 */
#define BUTTON_UP_PIN 4
#define BUTTON_OK_PIN 5
#define BUTTON_DOWN_PIN 2
#define BUTTON_CANCEL_PIN 3

/* 两种消抖延时 */
#define SHAKE_DELAY_1 100
#define SHAKE_DELAY_2 20

void InitKeys(void);
bool DownKeyState(void);
bool DownKeyState2(void);
bool UpKeyState(void);
bool UpKeyState2(void);
bool EnterKeyState(void);
bool CancelKeyState(void);
bool EnterOrCancel(void);

#endif