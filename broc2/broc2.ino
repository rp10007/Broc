#include <Servo.h>

/* BRoC
 Simplest move wheels for a second each way.
 Then: test the servo: 45 degrees right and left
 Now the sonar. The first version will just go until less than 30 cm from something.
 
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
const int pingPin = 13;
boolean notfinished = true;
int ledpin=11;
Servo frontgear;
int frontgearpos = 0;
int frontgearadjust = 110; // we like 0 in the middle, also use this to compensate
long currentDistance = 0;
long distanceArray[10];

void setup()
{
  pinMode(Red_Wire_Control, OUTPUT);
  pinMode(Black_Wire_Control, OUTPUT);
  pinMode(enablePin, OUTPUT);
  frontgear.attach(9);
  frontgear.write(frontgearadjust);
  delay(2000);
  
}
 
void loop()
{
  long duration, cm;
  if(notfinished){
    digitalWrite(ledpin, HIGH);
  int speed = 255;  // this is about as low as you can reliably run my motor
  boolean dirn = HIGH;
  setMotor(speed, dirn);
    // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  cm = microsecondsToCentimeters(duration);
if(cm < 10){
      setMotor(0, dirn);
      setMotor(speed, !dirn);
      delay(500);
      setMotor(0, dirn);
  // scan -45 to 45 by 15, put in distancearray. go to best angle, forward i sec.
  // if nothing is better than 30, well then.
  notfinished = false;
  digitalWrite(ledpin, LOW);
  }
}
delay(100);
}
 
void setMotor(int speed, boolean dirn)
{
  analogWrite(enablePin, speed);
  digitalWrite(Red_Wire_Control, !dirn);
  digitalWrite(Black_Wire_Control, dirn);
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
