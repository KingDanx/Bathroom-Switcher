#include <Arduino.h>
#include <TM1637Display.h>
#define CLK 2
#define DIO 3
int counter = 0;
int minute = 60;
int hunned = 100;
int second = 0;
int delayTimer=1000;
int switchPin = 4;
int switchPin2 = 12;
int relayPin = 8;
int relayPin2 = 7;
int switchVal;
int switchVal2;
TM1637Display display(CLK, DIO);

void setup() {
  // put your setup code here, to run once:
pinMode(switchPin, INPUT);
pinMode(relayPin, OUTPUT);
pinMode(switchPin2, INPUT);
pinMode(relayPin2, OUTPUT);
display.setBrightness(0x0f);
digitalWrite(switchPin, HIGH);
digitalWrite(switchPin2, HIGH);
Serial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:

switchVal = digitalRead(switchPin);
switchVal2 = digitalRead(switchPin2);

if(switchVal == 0 && switchVal2 == 0)
  {
    digitalWrite(relayPin, HIGH);
    digitalWrite(relayPin2, LOW);
  if(counter<=60)
  {
    display.showNumberDecEx(second,0b01000000,true,4,0);

    if(counter>=59)
     {
      counter=-1;
      second=second+hunned-minute;
     }
    if(second==9959)
     {
      counter=0;
      second=0;
     }
      counter++;
      second++;
      delay(delayTimer);
      Serial.print("Second: ");
      Serial.print(second);
      Serial.print(" || Counter: ");
      Serial.println(counter); 
  }
}  
else
  {
    display.showNumberDecEx(0,0b01000000,true,4,0);
    digitalWrite(relayPin2, HIGH);
    digitalWrite(relayPin, LOW);
    counter=0;
    second=0;
  }
}
