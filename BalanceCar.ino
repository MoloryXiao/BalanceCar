#include "MPU6050.h"
#include "Menu.h"
#include "Motor_Control.h"
#include "AdjMotor.h"
#include "E2prom.h"

#define DEBUG_PIN 10

unsigned long runTime = 0;
unsigned long nowTime = 0;
const unsigned long ms20 = 20;
typedef enum {
  OLED = 1,
  RUN = 2
} Main_Mode;

extern u8 expMotorFlag;
unsigned char mode = OLED;
extern u8 OLEDFlag;
float carAngle = 0.0, carAngleSpeed = 0.0, ans = 0.0;

// D0 D1 RST DC
OLED_SPI MyOLED(6, 12, 7, 13);
void setup() {
  // motor init
  Serial1.begin(115200);
  Serial.begin(115200);

  // OLED init and E2PROM init
  Wire.begin();             // 设置主机模式 I2C启动
  MyOLED.Init();            // 包含了对OLED引脚的初始化
  InitKeys();               // 按键初始化
  GetParamData();           // 获取PID值
  OLED_FirstPrint(MyOLED);  // 显示初始化

  // MPU6050 init
  initMPU6050();
  pinMode(DEBUG_PIN, OUTPUT);
}

void loop() {
  switch (mode) {
    case OLED:
      FirstLevelMenu(MyOLED);
      if (expMotorFlag == 1) {
        mode = RUN;
      }
      break;
    case RUN:
      // MPU6050 calc
      getMPU6050Data(&carAngle, &carAngleSpeed);
      ans = AngleControl(carAngle, carAngleSpeed);
      /*
      Serial.print(g_fGravityAngle);
      Serial.print('\t');
      Serial.print(g_fGyroscopeAngleSpeed / 10);
      Serial.print('\t');
      Serial.print(g_fCarAngle);
      Serial.print('\t');
      Serial.print(ans);
      Serial.println();
      */
      
      // send data to ATmega328
      MotorControl(-ans, 0);
      // stop run mode and return to debug mode
      if (CancelKeyState() == true) {
        mode = OLED;
        expMotorFlag = 0;
        sndspeed(0, 0);
        OLED_ReturnPrint(MyOLED);
      }
      delay(15);
      break;
  }
}

