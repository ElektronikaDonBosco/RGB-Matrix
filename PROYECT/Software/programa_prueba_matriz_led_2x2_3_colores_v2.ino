#include "Tlc5940.h"

int E0=16;
int E1=17;
int E2=18;
int E3=19;
int E4=20;

int channel1 = 0;
int channel2 = 1;
int channel3 = 2;
int channel4 = 3;
int channel5 = 4;
int channel6 = 5;

int green;
int red;
int blue;
int tempo;

void setup() {
pinMode(E0,OUTPUT);
pinMode(E1,OUTPUT);
pinMode(E2,OUTPUT);
pinMode(E3,OUTPUT);
pinMode(E4,OUTPUT);

tempo=200;
green=4000;
red=4000;
blue=4000; 

digitalWrite (E0,HIGH);
digitalWrite (E1,HIGH);
digitalWrite (E2,HIGH);
digitalWrite (E3,HIGH);
digitalWrite (E4,HIGH);
Tlc.init();
Tlc.clear();
}

void loop() {
  // RED
digitalWrite (E0,LOW);
digitalWrite (E1,LOW);
digitalWrite (E2,LOW);
digitalWrite (E3,LOW);
digitalWrite (E4,LOW);
Tlc.set(channel1, red);
Tlc.set(channel2, red);
Tlc.update();

delayMicroseconds(tempo);
Tlc.clear();
Tlc.update();

delayMicroseconds(tempo);
digitalWrite (E0,HIGH);
digitalWrite (E1,LOW);
digitalWrite (E2,LOW);
digitalWrite (E3,LOW);
digitalWrite (E4,LOW);
Tlc.set(channel1, red);
Tlc.set(channel3, red);
Tlc.update();

delayMicroseconds(tempo);
Tlc.clear();
Tlc.update();

  // GREEN

//digitalWrite (E0,LOW);
//digitalWrite (E1,LOW);
//digitalWrite (E2,LOW);
//digitalWrite (E3,LOW);
//digitalWrite (E4,LOW);
//Tlc.set(channel2, green);
//Tlc.set(channel4, green);
//Tlc.update();
//
//delayMicroseconds(tempo);
//Tlc.clear();
//Tlc.update();
//
//delayMicroseconds(tempo);
//digitalWrite (E0,HIGH);
//digitalWrite (E1,LOW);
//digitalWrite (E2,LOW);
//digitalWrite (E3,LOW);
//digitalWrite (E4,LOW);
//Tlc.set(channel2, green);
//Tlc.set(channel4, green);
//Tlc.update();
//
//delayMicroseconds(tempo);
//Tlc.clear();
//Tlc.update();

  // BLUE
//digitalWrite (E0,LOW);
//digitalWrite (E1,LOW);
//digitalWrite (E2,LOW);
//digitalWrite (E3,LOW);
//digitalWrite (E4,LOW);
//Tlc.set(channel3, blue);
//Tlc.set(channel6, blue);
//Tlc.update();
//
//delayMicroseconds(tempo);
//Tlc.clear();
//Tlc.update();
//
//delayMicroseconds(tempo);
//digitalWrite (E0,HIGH);
//digitalWrite (E1,LOW);
//digitalWrite (E2,LOW);
//digitalWrite (E3,LOW);
//digitalWrite (E4,LOW);
//Tlc.set(channel3, blue);
//Tlc.set(channel6, blue);
//Tlc.update();
//
//delayMicroseconds(tempo);
//Tlc.clear();
//Tlc.update();

}
