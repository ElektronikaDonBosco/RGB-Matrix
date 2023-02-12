//los pines que sean.
#include "Tlc5940.h"
int mux1[5]= {23,22,21,9,8};
int mux2[5]= {20,19,18,17,16};


//linea off
int lineOFF=21;

//lineas multiplex1. Están ordenados por línea y R, luego BG: 1R, 1BG, 2R, 2BG...
int linesMux1R[9]={5,9,13,30,14,10,6,2,0};
int linesMux1GB[9]={3,7,11,15,31,12,8,4,1};

//lineas multiplex2. Están ordenados por línea y R, luego BG: 10R, 10BG, 11R, 11BG...
int linesMux2R[9]={31,14,12,10,8,6,4,1,0};
int linesMux2GB[9]={30,15,13,11,9,7,5,3,2};

// canales
int Red1=0;
int Green1=1;
int Blue1=2;




void setup() {
  Serial.begin(9600);
  Tlc.init();
  //inicializa los pines 0
  for (int x = 0; x < 5; x++) {
    pinMode(mux1[x], OUTPUT);
    digitalWrite(mux1[x], LOW);
  }
   for (int x = 0; x < 5; x++) {
    pinMode(mux2[x], OUTPUT);
    digitalWrite(mux2[x], LOW);
  }


switchOff();
delay(1000);
lineSelect(mux1,linesMux1R[0]);
Tlc.set(Red1,3000);
Tlc.update();
//lineSelect(mux2, lineOFF);
//delay(1000);
//switchOff();

  
//  for (int x = 1; x<9; x++){
//      lineSelect(mux1,linesMux1R[x]);
//      delay(10);
//      //lineSelect(mux1, lineOFF);
//    }
//    lineSelect(mux1, lineOFF);
//    
//    for (int x = 0; x<9; x++){
//      lineSelect(mux2,linesMux2R[x]);
//      delay(100);
//    }
//    lineSelect(mux2, lineOFF);
//        
//        for (int x = 0; x<9; x++){
//      lineSelect(mux1,linesMux1GB[x]);
//      delay(100);
//    }
//    lineSelect(mux1, lineOFF);
//    
//  for (int x = 0; x<9; x++){
//      lineSelect(mux2,linesMux2GB[x]);
//      delay(100);
//    }
//    lineSelect(mux2, lineOFF);
//  Tlc.set(R1,3000);
//  Tlc.update();
// lineSelect(mux1,linesMux1R[0]);


}

void loop() {
//  lineSelect(mux2, lineOFF);
//  Tlc.set(R1,300);
//  Tlc.update();
// lineSelect(mux1,linesMux1R[0]);
// delayMicroseconds(100);
// lineSelect(mux1, lineOFF);
// lineSelect(mux2, lineOFF);
//  Tlc.set(Blue1,300);
//  Tlc.update();
// lineSelect(mux1,linesMux1R[0]);
// delayMicroseconds(100);
// lineSelect(mux1, lineOFF);
// lineSelect(mux2, lineOFF);
//  Tlc.set(G1,3000);
//  Tlc.update();
// lineSelect(mux1,linesMux1R[0]);
// delayMicroseconds(100);
// lineSelect(mux1, lineOFF);
// lineSelect(mux2, lineOFF);
  // put your main code here, to run repeatedly:
// for (int x = 1; x<9; x++){
//      lineSelect(mux1,linesMux1R[x]);
//      delay(10);
//      pintarlinea();
//      //lineSelect(mux1, lineOFF);
//    }
//    lineSelect(mux1, lineOFF);
//    
//    for (int x = 0; x<9; x++){
//      lineSelect(mux2,linesMux2R[x]);
//      delay(100);
//      pintarlinea();
//    }
//    lineSelect(mux2, lineOFF);
//        
//        for (int x = 0; x<9; x++){
//      lineSelect(mux1,linesMux1GB[x]);
//      delay(100);
//      pintarlinea();
//    }
//    lineSelect(mux1, lineOFF);
//    
//  for (int x = 0; x<9; x++){
//      lineSelect(mux2,linesMux2GB[x]);
//      delay(100);
//      pintarlinea();
//    }
//    lineSelect(mux2, lineOFF);
// 
// 
//  
}

/*COMENTARIO QUÉ REALIZA ESTA FUNCIÓN*/
void lineSelect(int mux[], int pinnum){
  for (int x = 0; x<5; x++){
      byte state = bitRead(pinnum, x);
      digitalWrite(mux[x], state); 
}
}

/*COMENTARIO QUÉ REALIZA ESTA FUNCIÓN*/
void switchOff (){
lineSelect(mux1, lineOFF);
lineSelect(mux2, lineOFF);
Tlc.clear();
Tlc.update();
  }
