//Written by ShoelessJo3
//2/28/18 

#include <Servo.h>

Servo motor2;
Servo motor1;


int topTarget = 200;
int botTarget = 0;
int numMotors = 2;
int ChA[] = {9, 13};
int ChB[] = {10, 12};

float rot[] = {0,0};
float dist[] = {0,0};
int lastPos[] = {0,0};
int curPos[] = {0,0};
int oldPos[] = {0,0};
int controlPin = 2;
int threshPos = 4; //within 2 rotations
float targetPos[] = {0,0};
int maxPos = 200; //for smoothing purposes
int motorPin[] = {6,11};


void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(ChA, INPUT);
pinMode(ChB, INPUT);
pinMode(motorPin, OUTPUT);
pinMode(controlPin,INPUT);
motor2.attach(motorPin[1]);
motor1.attach(motorPin[0]);
}

void loop() {
  // put your main code here, to run repeatedly
  for(int m = 0; m<numMotors; m++)
  {
    curPos[m] = getPos(m);
    dist[m] = rot[m]/4;
  //get current position from motor
    if(digitalRead(controlPin))
    {
      targetPos[m] = topTarget;
    }
    else
    {
     targetPos[m] = botTarget;
    }


    
  if(abs(targetPos[m] - dist[m]) <= threshPos)
  {
    if(m == 1)
      motor2.write(90);
    else
      motor1.write(90);
  }
  else if(targetPos[m] - dist[m] < 0) //overshot go backwards
    {
      //Serial.println("it goes backwards");
      if(m == 1)
      {
        motor2.write(60);
        Serial.println("it goes backwards");
      
     }
     else
      motor1.write(60);
  }  
  else if(targetPos[m] - dist[m] > 0){
    Serial.println("it goes forwards");
    if(m == 1)
      {
        motor2.write(110 + 20*((float)(abs(targetPos[m] -dist[m])/(float)maxPos)));
        //Serial.println(110 + 20*((float)(abs(targetPos[m] -dist[m])/(float)maxPos)));
      }
    else
      motor1.write(110 + 20*((float)(abs(targetPos[m] -dist[m])/(float)maxPos)));

  }

  
 /*  Serial.print(dist[m]);
   Serial.print(" ");
   Serial.println(m);*/
  if(curPos[m] != oldPos[m])
  {
    if((curPos[m] == 4 && oldPos[m] == 1) || curPos[m] - oldPos[m] > 0)
    {
      rot[m] += 1;
    }
    else
    {
      rot[m] -= 1;
    }
  }
  oldPos[m] = curPos[m];
  }
}



int getPos(int motorPin){

  int a = digitalRead(ChA[motorPin]);
  int b = digitalRead(ChB[motorPin]);

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

