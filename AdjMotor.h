#ifndef ADJMOTOR_H_
#define ADJMOTOR_H_

#include "MPU6050.h"
#include "EEPROM.h"

extern PARAM_ROM V_P_Param;
extern PARAM_ROM V_I_Param;
extern PARAM_ROM D_P_Param;
extern PARAM_ROM D_D_Param;
extern PARAM_ROM A_P_Param;
extern PARAM_ROM A_D_Param;

#define CAR_ANGLE_SET		0
#define CAR_ANGLE_SPEED_SET	0

#define CAR_SPEED_CONSTANT	0
#define CAR_SPEED_SETfDelta	0
#define SPEED_CONTROL_PERIOD	100 

float speedControlOutOld = 0.0;
float speedControlIntegral = 0.0;
float speedControlOutNew = 0.0;

// return angle control result
float AngleControl(float carAngle, float gyroscopeAngleSpeed)
{
	float value;
	
	value = (CAR_ANGLE_SET - carAngle) * A_P_Param.GetParamFloatValue() + (CAR_ANGLE_SPEED_SET - gyroscopeAngleSpeed) *A_D_Param.GetParamFloatValue();
	//value = (CAR_ANGLE_SET - carAngle) * 0.5 + (CAR_ANGLE_SPEED_SET - gyroscopeAngleSpeed) * 0;
	
	// if (value > ANGLE_CONTROL_OUT_MAX) 
		// value = ANGLE_CONTROL_OUT_MAX;
	// else if (value < ANGLE_CONTROL_OUT_MIN)
		// value = ANGLE_CONTROL_OUT_MIN;
	
	return value;
}

// return speed control result
float SpeedControl(float LSpeed, float RSpeed)
{
	float fDelta;
	float fP, fI;
	float carSpeed;
	float value;
	float speedControlOut; 
	float speedControlPeriod;
	
	carSpeed = (LSpeed + RSpeed) / 2.0;
	carSpeed *= CAR_SPEED_CONSTANT;
	
	fDelta = CAR_SPEED_SETfDelta - carSpeed;
	fP = fDelta * V_P_Param.GetParamFloatValue();
	fI = fDelta * V_I_Param.GetParamFloatValue();
	
	speedControlIntegral += fI;
	
	speedControlOutOld = speedControlOutNew;
	speedControlOutNew = fP + speedControlIntegral;
	
	value = speedControlOutNew - speedControlOutOld;
	speedControlOut = value * (speedControlPeriod + 1) / SPEED_CONTROL_PERIOD + speedControlOutOld;
	
	return speedControlOut;
}

float MotorControl(float angleControl, float speedControl)
{
	float LMotor, RMotor;
	
	LMotor = angleControl - speedControl;
	RMotor = angleControl - speedControl;

  if(LMotor >= 0)LMotor+=20;
  else LMotor-=20;

    if(RMotor >= 0)RMotor+=20;
  else RMotor-=20;
  
	sndspeed(LMotor, RMotor);
}

#endif ADJMOTOR_H_
