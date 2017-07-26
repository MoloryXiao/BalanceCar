//MPU-UNO
//VCC-VCC
//GND-GND
//SCL-A5
//SDA-A4
#ifndef MPU6050_H_
#define MPU6050_H_

#include <Wire.h>
#include <math.h>

const unsigned char kValCnt = 7;
const unsigned char kMpuAddr = 0x68;

float g_fGyroscopeAngleSpeed = 0;
float g_fGravityAngle = 0;
float g_fCarAngle = 0;
float g_fGyroscopeAngleIntegral = 0;

float VOLTAGE_GYRO = 0;                                                   //  定义陀螺仪（选X,Y,Z）
float VOLTAGE_GRAVITY = 0;                                                //  定义加速度计（选X,Y,Z）
const float GRAVITY_OFFSET = 300;                                         //  加速度计零偏
const float GRAVITY_ANGLE_RATIO = (float)180 / 32768 ;                    //  加速度计归一化因子
const float GYROSCOPE_OFFSET = -250;                                      //  陀螺仪零偏移
const float GYROSCOPE_ANGLE_RATIO = (float)350 / 32767;                   //  归一化因子
const float GRAVITY_ADJUST_TIME_CONSTANT =  2;                            //  陀螺仪加速度计加和的比例因子
const float GYROSCOPE_ANGLE_SIGMA_FREQUENCY = 50;                         //  积分的频率

short readouts[kValCnt] = {0};



/*********************************************************
  Function:  Wirte one byte of data to the MPU6050
  Parameter:  by_reg, register address
      n_val, data value
  return:   void
**********************************************************/
void WriteMpuReg(short by_reg, unsigned char  n_val) {
  Wire.beginTransmission(kMpuAddr);         // START transmission
  Wire.write(by_reg);                       // specify register address
  Wire.write(n_val);                        // wirte data
  Wire.endTransmission(true);               // close transmission and relinquish the BUS
}

//unsigned char ReadMpuReg(int by_reg) {
//  Wire.beginTransmission(kMpuAddr);         // START transmission
//  Wire.write(by_reg);                       // specify register address
//  Wire.requestFrom(kMpuAddr, 1, true);      // read data to buff
//  Wire.endTransmission(true);               // close transmission and relinquish the BUS
//
//  return Wire.read();
//}

void ReadAccGyr(short *pVals) {
  Wire.beginTransmission(kMpuAddr);
  Wire.write(0x3B);
  Wire.requestFrom(kMpuAddr, kValCnt * 2, true);
  Wire.endTransmission(true);
  for (char i = 0; i < kValCnt; i++) {
    pVals[i] = Wire.read() << 8 | Wire.read();
  }
}

void AngleCalculate(void) {

  float fDeltaValue;

  VOLTAGE_GRAVITY = readouts[1];
  if (VOLTAGE_GRAVITY > 18000) VOLTAGE_GRAVITY = 0;

  VOLTAGE_GYRO = readouts[4];

  // 加速度计读取的数值转换为角度
  g_fGravityAngle = (VOLTAGE_GRAVITY - GRAVITY_OFFSET) * GRAVITY_ANGLE_RATIO; //  g_fGravityAngle = 0;

  // 陀螺仪获取角速度
  g_fGyroscopeAngleSpeed = (VOLTAGE_GYRO - GYROSCOPE_OFFSET) * GYROSCOPE_ANGLE_RATIO;

  // 车身角度计算
  g_fCarAngle = g_fGyroscopeAngleIntegral;
  fDeltaValue = (g_fGravityAngle - g_fCarAngle) / GRAVITY_ADJUST_TIME_CONSTANT;
  g_fGyroscopeAngleIntegral += (g_fGyroscopeAngleSpeed + fDeltaValue) / GYROSCOPE_ANGLE_SIGMA_FREQUENCY;

}

void initMPU6050(void)
{
  Wire.begin();
  WriteMpuReg(0x6B, 0);
  ReadAccGyr(readouts);     // read data from MPU6050
  AngleCalculate();
}

float getMPU6050Data(float *carAngle, float *carAngleSpeed)
{

    ReadAccGyr(readouts);     // read data from MPU6050
    AngleCalculate();

    *carAngle = g_fCarAngle;
    *carAngleSpeed = g_fGyroscopeAngleSpeed;

}

//void CalculateGravityOffset(void)
//{
//
//}

//void setup() {
//
//  //setup code here, to run once:
//  //Serial.begin(115200);
//  Wire.begin();
//  WriteMpuReg(0x6B, 0);
//
//  ReadAccGyr(readouts);     // read data from MPU6050
//  AngleCalculate();
//
//}



//void loop() {
//
//  nowTime=millis();
//  if((nowTime - runTime) >= ms20 )
//  {
//    runTime = nowTime;
//    ReadAccGyr(readouts);     // read data from MPU6050
//    AngleCalculate();
////    Serial.print(g_fGravityAngle);
////    Serial.print('\t');
////    Serial.print(g_fGyroscopeAngleSpeed/10);
////    Serial.print('\t');
////    Serial.print(g_fCarAngle);
////    Serial.println();
//  }

//}

#endif



