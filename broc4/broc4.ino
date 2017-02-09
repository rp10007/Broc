#include <IRremote.h>


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
int irPin = 2;
IRrecv irrecv(irPin);
decode_results result;

void setup()
{
  pinMode(Red_Wire_Control, OUTPUT);
  pinMode(Black_Wire_Control, OUTPUT);
  pinMode(enablePin, OUTPUT);
  frontgear.attach(9);
  frontgear.write(frontgearadjust);
  delay(500);
  irrecv.enableIRIn();
}
 
void loop()
{
  if(notfinished){
    digitalWrite(ledpin, HIGH);
  int speed = 255;
  boolean dirn = HIGH;
  
   if (irrecv.decode(&result)) {
    switch(result.value){
      case 0xff629d: //fwd
          setMotor(speed, dirn);
          break;
      case 0xff02fd: //okront
          setMotor(0, dirn);
          break;
      case 0xffa857: //back
          setMotor(speed, !dirn);
          break;
      case 0xff4ab5: //0
          notfinished = false;
          digitalWrite(ledpin, LOW);
          break;
      case 0xff22dd: //left
          frontgearpos = min(frontgearpos + 30, 30);
          frontgear.write(frontgearpos + frontgearadjust);
          break;
     case 0xffc23d: //right
         frontgearpos = max(frontgearpos - 30, -30);
         frontgear.write(frontgearpos + frontgearadjust);
         break;
         //default:
         //nothing here right now
    }
      
    irrecv.resume(); // Receive the next value
   }
  }
}
 
void setMotor(int speed, boolean dirn)
{
  analogWrite(enablePin, speed);
  digitalWrite(Red_Wire_Control, !dirn);
  digitalWrite(Black_Wire_Control, dirn);
}

