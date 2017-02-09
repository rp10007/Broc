#include <Servo.h>

/* BRoC
 Simplest version: move wheels for a second each way.
 Next: test the servo
 More functions as they are added.
 
 Code modeled on:
 Adafruit motor tutorial
 ping
 servo example code
 
  This version runs on Teensy 2.0. Pins will need to change for other 
 boards. enablePin and servoPin must be able to do PWM
 */
 
int Red_Wire_Control = 0;
int Black_Wire_Control = 1;
int enablePin = 11;  
int servoPin = 9;
boolean notfinished = true;
int ledpin=11;
Servo frontgear;
int frontgearpos = 0;
int frontgearadjust = 100; // we like 0 in the middle, also use this to compensate
int currentDistance = 0;

void setup()
{
  pinMode(Red_Wire_Control, OUTPUT);
  pinMode(Black_Wire_Control, OUTPUT);
  pinMode(enablePin, OUTPUT);
  frontgear.attach(9);
}
 
void loop()
{
  if(notfinished){
    digitalWrite(ledpin, HIGH);
  int speed = 255;
  boolean dirn = HIGH;
  setMotor(speed, dirn);
  delay(1000);
  setMotor(speed, !dirn);
  delay(1000);
  setMotor(0, dirn);
  for(frontgearpos = 0; frontgearpos < 45; frontgearpos += 1)  
    { frontgear.write(frontgearpos+frontgearadjust);              
    delay(25);                      
    }
  for(frontgearpos = 45; frontgearpos>=-44; frontgearpos -= 1)    
  {                                
    frontgear.write(frontgearpos+frontgearadjust);             
    delay(25);  
  }
  for(frontgearpos = -45; frontgearpos < 0; frontgearpos += 1)  
      {
        frontgear.write(frontgearpos+frontgearadjust);              
        delay(25);    
  }
  notfinished = false;
  digitalWrite(ledpin, LOW);
  }
}
 
void setMotor(int speed, boolean dirn)
{
  analogWrite(enablePin, speed);
  digitalWrite(Red_Wire_Control, !dirn);
  digitalWrite(Black_Wire_Control, dirn);
}

