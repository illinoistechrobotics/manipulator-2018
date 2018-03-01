//Written by ShoelessJo3
//2/28/18 

#include <Servo.h>

Servo motor2;

int ChA = 13;
int ChB = 12;
float rot = 0;
float dist = 0;
int lastPos = 0;
int curPos = 0;
int oldPos = 0;
//int speed;
int threshPos = 4; //within 2 rotations
int targetPos = 200;
int maxPos = targetPos - dist;
int motorPin = 11;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(ChA, INPUT);
pinMode(ChB, INPUT);
pinMode(motorPin, OUTPUT);
motor2.attach(11);
}

void loop() {
  // put your main code here, to run repeatedly
    
  int curPos = getPos();
  int dist = rot/4;
  //get current position from motor

  
  if(targetPos - dist < 0 && abs(targetPos - dist) > threshPos) //overshot go backwards
  {
    motor2.write(100 - 30*((float)(abs(targetPos -dist)/(float)maxPos)));
    Serial.println(100 - 30*((float)(abs(targetPos -dist)/(float)maxPos)));
  }
  
  if(targetPos - dist > 0 && abs(targetPos - dist) > threshPos ){
     motor2.write(100 + 30*((float)(abs(targetPos -dist)/(float)maxPos)));
     Serial.println(100 + 30*((float)(abs(targetPos -dist)/(float)maxPos)));
  }

  if(abs(targetPos - dist) <= threshPos + 1)
  {
    motor2.write(90);
    Serial.println("you did it!");
  }
  
  
  Serial.println(dist);
  if(curPos != oldPos)
  {
    if((curPos == 4 && oldPos == 1) || curPos - oldPos > 0)
    {
      rot += 1;
    }
    else
    {
      rot -= 1;
    }
  }
  oldPos = curPos;
}



int getPos(){

  int a = digitalRead(ChA);
  int b = digitalRead(ChB);

  if(!a && !b)
  {
    return 1;
  }
  if(!a && b)
  {
    return 2;
  }
  if(a && b)
  {
    return 3;
  }
  if(a && !b)
  {
    return 4;
  }
  
}

