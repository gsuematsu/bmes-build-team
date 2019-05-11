// Circuit Key:
// Joystick or potentiometer should be plugged into A0
// Servo should be plugged into D9

#include <Servo.h>

Servo myServo;  // create servo object to control a servo

int pinPot = A0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
int pos;
int vel;
int pinServo = 9;

void setup() {
  
  myServo.attach(pinServo);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
  val = analogRead(pinPot);            // reads the value of the potentiometer (value between 0 and 1023)
  vel = getVelocity(val);
  pos = updatePos(pos, vel);     // scale it to use it with the servo (value between 0 and 180)
  Serial.print(vel); Serial.print(' ');
  Serial.println(val);
  myServo.write(pos);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}

int getVelocity(int valGV){
  int velGV;
  valGV -= 511;
  if(abs(valGV) < 25){
    velGV = 0;
  }
  else{
    velGV = valGV/100;
  }

  return velGV;
}

int updatePos(int currentPosUP, int velUP){
  int newPos = currentPosUP;
  bool shouldUpdatePos = true;
  if(velUP < 0 && currentPosUP - velUP < 0){
    shouldUpdatePos = false;
  }
  if(velUP > 0 && currentPosUP + velUP > 180){
    shouldUpdatePos = false;
  }
  if(shouldUpdatePos){
    newPos = currentPosUP + velUP;
  }

  return newPos;
}
