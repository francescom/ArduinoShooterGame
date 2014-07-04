
#include <HT1632.h>

#include <images.h>
#include "game.h"



const int xAxis = A0;         // joystick X axis
const int yAxis = A1;         // joystick Y axis
char butnR=3, butnT=4, butnB=5, butnL=6;
char butnJ=2;
int xValue;
int yValue;

boolean btnJPress=false;
boolean btnLPress=false;
boolean btnTPress=false;
boolean btnRPress=false;
boolean btnBPress=false;

unsigned long millisTime;







void setup () {
  Serial.begin(9600);
  HT1632.begin(9, 10, 11,12 );
  pinMode(butnJ, INPUT);      //Set the Joystick 'Select'button as an input
  digitalWrite(butnJ, HIGH);  //Enable the pull-up resistor on the select button
  pinMode(butnL, INPUT);      //Set the Joystick button as an input
  digitalWrite(butnL, HIGH);  //Enable the pull-up resistor on button
  pinMode(butnR, INPUT);      //Set the Joystick button as an input
  digitalWrite(butnR, HIGH);  //Enable the pull-up resistor on button
  pinMode(butnT, INPUT);      //Set the Joystick button as an input
  digitalWrite(butnT, HIGH);  //Enable the pull-up resistor on button
  pinMode(butnB, INPUT);      //Set the Joystick button as an input
  digitalWrite(butnB, HIGH);  //Enable the pull-up resistor on button
  
  millisTime=millis();
  gameSetup();
}

void loop() {
 
  xValue=analogRead(xAxis)-512;
  yValue=-analogRead(yAxis)+512;
  
  btnJPress=btnJPress || (digitalRead(butnJ) == LOW);
  btnLPress=btnLPress || (digitalRead(butnL) == LOW);
  btnTPress=btnTPress || (digitalRead(butnT) == LOW);
  btnRPress=btnRPress || (digitalRead(butnR) == LOW);
  btnBPress=btnBPress || (digitalRead(butnB) == LOW);
  
  if(millis() - millisTime > 60) {
    gameLoop(xValue,yValue,btnJPress,btnLPress,btnTPress,btnRPress,btnBPress);
    btnJPress=btnLPress=btnTPress=btnRPress=btnBPress=false;
    millisTime=millis();
  }
}

