#ifndef GET_MOTOR_SPEED_H_
#define GET_MOTOR_SPEED_H_

#define Int0 2    // digital 2
#define Int1 3    // digital 3

int l_wheel = 0;    
int r_wheel = 0;
int l_wheel_last = 0;
int r_wheel_last = 0;

int l_inPin = 4;
int r_inPin = 5;

int l_change_val = 0;
int r_change_val = 0;

int int_time = 10;

// void loop()
// {
  // /* add main program code here */
  // RtnSpeed();
  // SndSpeed(100,100);
// }

void SndSpeed(signed int left,signed int right)
{
   Serial.print("s");
   Serial.print(left);
   Serial.print(",");
   Serial.print(right);
   Serial.print("e");   
}

void LCount()
{
  if (digitalRead(l_inPin) == HIGH){
    l_wheel++;
  }
  else{
    l_wheel--;
  }
}

void RCount()
{

  if (digitalRead(r_inPin) == HIGH){
    r_wheel--;
  }
  else{
    r_wheel++;
  }
}

void init_getMotorSpeed(void)
{
  /* add setup code here */
  attachInterrupt(Int0, LCount, RISING);
  attachInterrupt(Int1, RCount, RISING);
  pinMode(l_inPin, INPUT);
  pinMode(r_inPin, INPUT);
  l_wheel = 0;
  r_wheel = 0; 
}

void RtnSpeed(int *LMotor, int *RMotor)
{
  unsigned long nowtime = millis();
  if (nowtime > int_time){
    l_change_val = l_wheel - l_wheel_last;
    r_change_val = r_wheel - r_wheel_last;
    int_time = nowtime;
    int_time += 10;
    l_wheel_last = l_wheel;
    r_wheel_last = r_wheel;
   // Serial.print("r");
   // Serial.print(l_change_val);
   // Serial.print(",");
   // Serial.print(r_change_val);
   // Serial.print("t");  
	*LMotor = l_change_val;
	*RMotor = r_change_val;
  }
}

#endif
