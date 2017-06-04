// This is my robot control program written in Jan/Feb 2017 by seobeq.
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdlib.h>
#include <ncurses.h>

#define TRIG 5
#define ECHO 6

void setup();
void forward();
void backward();
void stop();
void turnleft();
void turnright();
int getCM();
int distLeft = 0;
int distRight = 0;

int main(){
wiringPiSetup();
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);
pinMode(14,OUTPUT);
pinMode(30, OUTPUT);
softPwmCreate(22, 0, 40);
softPwmCreate(21, 0, 40);

while(1){
setup();
//getCM();
if(getCM() <= 25)
{
stop();
delay(1000);
distLeft = lookLeft();
//delay(1000);
distRight = lookRight();

if(distLeft >= distRight){
turnleft();
delay(350);
stop();
delay(1000);
}

else{
turnright();
delay(350);
stop();
delay(1000);
}
}
forward();
//delay(1000);
}
}


void forward(){
softPwmWrite(21, 40);
softPwmWrite(22, 40);
digitalWrite(12, LOW);//Left
digitalWrite(13, HIGH);//
digitalWrite(14, LOW);//Right
digitalWrite(30, HIGH);//
}
void backward(){
softPwmWrite(21, 40);
softPwmWrite(22, 40);
digitalWrite(12, HIGH);
digitalWrite(13, LOW);
digitalWrite(14, HIGH);
digitalWrite(30, LOW);
}
void stop(){
digitalWrite(12, LOW);
digitalWrite(13, LOW);
digitalWrite(14, LOW);
digitalWrite(30, LOW);
}
void turnright(){
softPwmWrite(21, 40);
softPwmWrite(22, 40);
digitalWrite(12, HIGH);
digitalWrite(13, LOW);
digitalWrite(14, LOW);
digitalWrite(30, HIGH);
}
void turnleft(){
softPwmWrite(21, 40);
softPwmWrite(22, 40);
digitalWrite(12, LOW);
digitalWrite(13, HIGH);
digitalWrite(14, HIGH);
digitalWrite(30, LOW);
}

void setup(){
pinMode(TRIG, OUTPUT);
pinMode(ECHO, INPUT);

//TRIG pin must start LOW
digitalWrite(TRIG, LOW);
delay(30);
}

int getCM() {
//Send trig pulse
digitalWrite(TRIG, HIGH);
delayMicroseconds(20);
digitalWrite(TRIG, LOW);
//Wait for echo start
while(digitalRead(ECHO) == LOW);
//Wait for echo end
long startTime = micros();
while(digitalRead(ECHO) == HIGH);
long travelTime = micros() - startTime;
//Get distance in cm
int distance = travelTime / 58;
return distance;
}

int lookLeft(){
turnleft();
delay(500);
int distance = getCM();
turnright();
delay(500);
return distance;
}

int lookRight(){
turnright();
delay(500);
int distance = getCM();
turnleft();
delay(500);
return distance;
}
