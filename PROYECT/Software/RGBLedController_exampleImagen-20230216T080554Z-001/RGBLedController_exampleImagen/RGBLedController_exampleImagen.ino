//Librerias
#include "Tlc5940.h"
#include <Bounce.h>
#include <elapsedMillis.h>
//variable tiempo espera


//Salidas del Teensy que controlan los dos multiplexores (A0,A1,A2,A3,A4)
int mux1[5] = {23,22,21,9,8};
int mux2[5] = {20,19,18,17,16};

//ADG732 enables
int enable1 = 15;
int enable2 = 14;

//linea off
int lineOFF = 21;

//TLC5940 maxímos pasos en la escala de grises (son 4096 niveles, de 0 a 4095)
int maxSteps = 4095;

//Los leds tendrán una resolución de 8 bits, es decir, de 0 a 255 niveles
int maxResolution = 255;

//lineas multiplex1. Están ordenados por línea y R, luego BG: 1R, 1BG, 2R, 2BG...9R, 9BG
int linesMux1R[9] = {5,9,13,30,14,10,6,2,0};
int linesMux1GB[9] = {3,7,11,15,31,12,8,4,1};

//lineas multiplex2. Están ordenados por línea y R, luego BG: 10R, 10BG, 11R, 11BG...18R,18-bg
int linesMux2R[9] = {31,14,12,10,8,6,4,1,0};
int linesMux2GB[9] = {30,15,13,11,9,7,5,3,2};

// Canales. Hay 6 drivers en cascada. Cada uno de 16 entradas/salidas. Se numeran:0,1,2 red, green, blue sucesivamente
int ledRed[32] = {0,3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48,51,54,57,60,63,66,69,72,75,78,81,84,87,90,93};
int ledGreen[32] = {1,4,7,10,13,16,19,22,25,28,31,34,37,40,43,46,49,52,55,58,61,64,67,70,73,76,79,82,85,88,91,94};
int ledBlue[32] = {2,5,8,11,14,17,20,23,26,29,32,35,38,41,44,47,50,53,56,59,62,65,68,71,74,77,80,83,86,89,92,95};


//delay time
int delaySeconds = 10;
int delayMicros = 1;


//IMAGEN CREADA EN PAINT.  
byte red [18][32] = {
{0, 0, 237, 237, 237, 237, 237, 237, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 237, 237, 237, 237, 237, 237, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 237, 237, 237, 237, 237, 237, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 237, 237, 237, 237, 237, 237, 0, 0, 0, 0, 0, 0, 0, 0, 0, 34, 34, 34, 34, 34, 34, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 237, 237, 237, 237, 237, 237, 0, 0, 0, 0, 0, 0, 0, 0, 0, 34, 34, 34, 34, 34, 34, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 237, 237, 237, 237, 237, 237, 0, 0, 0, 0, 0, 0, 0, 0, 0, 34, 34, 34, 34, 34, 34, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 34, 34, 34, 34, 34, 34, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 63, 63, 63, 63, 63, 63, 63, 0, 0, 0, 0, 34, 34, 34, 34, 34, 34, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 63, 63, 63, 63, 63, 63, 63, 0, 0, 0, 0, 34, 34, 34, 34, 34, 34, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 63, 63, 63, 63, 63, 63, 63, 0, 0, 0, 0, 34, 34, 34, 34, 34, 34, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 63, 63, 63, 63, 63, 63, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 63, 63, 63, 63, 63, 63, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 63, 63, 63, 63, 63, 63, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 63, 63, 63, 63, 63, 63, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 63, 63, 63, 63, 63, 63, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
byte green [18][32] = {
{0, 0, 28, 28, 28, 28, 28, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 28, 28, 28, 28, 28, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 28, 28, 28, 28, 28, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 28, 28, 28, 28, 28, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 177, 177, 177, 177, 177, 177, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 28, 28, 28, 28, 28, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 177, 177, 177, 177, 177, 177, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 28, 28, 28, 28, 28, 28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 177, 177, 177, 177, 177, 177, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 177, 177, 177, 177, 177, 177, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 72, 72, 72, 72, 72, 72, 72, 0, 0, 0, 0, 177, 177, 177, 177, 177, 177, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 72, 72, 72, 72, 72, 72, 72, 0, 0, 0, 0, 177, 177, 177, 177, 177, 177, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 72, 72, 72, 72, 72, 72, 72, 0, 0, 0, 0, 177, 177, 177, 177, 177, 177, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 72, 72, 72, 72, 72, 72, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 72, 72, 72, 72, 72, 72, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 72, 72, 72, 72, 72, 72, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 72, 72, 72, 72, 72, 72, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 72, 72, 72, 72, 72, 72, 72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
byte blue [18][32] = {
  {0, 0, 36, 36, 36, 36, 36, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 36, 36, 36, 36, 36, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 36, 36, 36, 36, 36, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 36, 36, 36, 36, 36, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 76, 76, 76, 76, 76, 76, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 36, 36, 36, 36, 36, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 76, 76, 76, 76, 76, 76, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 36, 36, 36, 36, 36, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 76, 76, 76, 76, 76, 76, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 76, 76, 76, 76, 76, 76, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 204, 204, 204, 204, 204, 204, 204, 0, 0, 0, 0, 76, 76, 76, 76, 76, 76, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 204, 204, 204, 204, 204, 204, 204, 0, 0, 0, 0, 76, 76, 76, 76, 76, 76, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 204, 204, 204, 204, 204, 204, 204, 0, 0, 0, 0, 76, 76, 76, 76, 76, 76, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 204, 204, 204, 204, 204, 204, 204, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 204, 204, 204, 204, 204, 204, 204, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 204, 204, 204, 204, 204, 204, 204, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 204, 204, 204, 204, 204, 204, 204, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 204, 204, 204, 204, 204, 204, 204, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };
byte dataOff [32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void setup() {
  Serial.begin(9600);
  //Inicializar TLC
  Tlc.init();
  Tlc.clear();
  Tlc.update();
  
  //Inicializa enables del ADG732
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
  digitalWrite(enable1, HIGH);
  digitalWrite(enable2, HIGH);
  
  //inicializa los pines 0
  for (int x = 0; x < 5; x++) {
    pinMode(mux1[x], OUTPUT);
    digitalWrite(mux1[x], LOW);
  }
   for (int x = 0; x < 5; x++) {
    pinMode(mux2[x], OUTPUT);
    digitalWrite(mux2[x], LOW);
  }
//Tiempo para inicializar todo.
delay(1000);
}

void loop() {


for (int x=1; x<=18; x++){
   elapsedMicros timeoutR;
     while ( timeoutR < 600){
      lightLine('R', x, red[x-1]);
      //delayMicroseconds(delayMicros);
       
   }
     timeoutR = 0;
    }
 


for (int x=1; x<=18; x++){
  elapsedMicros timeoutG;
    while ( timeoutG < 600){
      lightLine('G', x, green[x-1]);
      //delayMicroseconds(delayMicros);
         
     }
   timeoutG = 0;
    }

  
for (int x=1; x<=18; x++){
  elapsedMicros timeoutB; 
    while (timeoutB < 600){
      lightLine('B', x, blue[x-1]);
      //delayMicroseconds(delayMicros);
        
    }
    timeoutB = 0;
    }


}




/*Muestra una línea en base a los datos de entrada dados:
-color de la línea
-número de la línea
-array de 32 bytes con los datos a mostrar*/
void lightLine(char color, int line, byte data[32]){
	
	//Case para diferenciar los distintos multiplexores/colores 
	switch (color){
		
		//Rojo
		case 'R':
   
		//Encendemos la fila adecuada
		if(line<10){
			digitalWrite(enable1, HIGH);
			digitalWrite(enable2, HIGH);
			//Actualizo valores de ROJO que vienen de data.
			for (int x = 0; x<32; x++){
				Tlc.set(ledRed[x], data[x]*maxSteps/maxResolution);        
			}
			Tlc.update();
			lineSelect(mux1, linesMux1R[line-1]);
			digitalWrite(enable1, LOW);
        }else{
			digitalWrite(enable1, HIGH);
			digitalWrite(enable2, HIGH);
			//Actualizo valores de ROJO que vienen de data.
			for (int x = 0; x<32; x++){
			Tlc.set(ledRed[x], data[x]*maxSteps/maxResolution);        
			}
			Tlc.update();
			lineSelect(mux2, linesMux2R[line-10]);
			digitalWrite(enable2, LOW);
		}
		break;
		
		//Green
		case 'G':
		
		//Encendemos la fila adecuada
		if(line<10){
			digitalWrite(enable1, HIGH);
			digitalWrite(enable2, HIGH);
			//Actualizo valores de VERDE que vienen de data.
			for (int x = 0; x<32; x++){
				Tlc.set(ledGreen[x], data[x]*maxSteps/maxResolution);        
			}
			Tlc.update();
			lineSelect(mux1, linesMux1GB[line-1]);
			digitalWrite(enable1, LOW);
        }else{
			digitalWrite(enable1, HIGH);
			digitalWrite(enable2, HIGH);
			//Actualizo valores de VERDE que vienen de data.
			for (int x = 0; x<32; x++){
			Tlc.set(ledGreen[x], data[x]*maxSteps/maxResolution);        
			}
			Tlc.update();
			lineSelect(mux2, linesMux2GB[line-10]);
			digitalWrite(enable2, LOW);
		}
		break;
		
		//Blue
		case 'B':
		
		//Encendemos la fila adecuada
		if(line<10){
			digitalWrite(enable1, HIGH);
			digitalWrite(enable2, HIGH);
			//Actualizo valores de VERDE que vienen de data.
			for (int x = 0; x<32; x++){
				Tlc.set(ledBlue[x], data[x]*maxSteps/maxResolution);        
			}
			Tlc.update();
			lineSelect(mux1, linesMux1GB[line-1]);
			digitalWrite(enable1, LOW);
        }else{
			digitalWrite(enable1, HIGH);
			digitalWrite(enable2, HIGH);
			//Actualizo valores de VERDE que vienen de data.
			for (int x = 0; x<32; x++){
			Tlc.set(ledBlue[x], data[x]*maxSteps/maxResolution);        
			}
			Tlc.update();
			lineSelect(mux2, linesMux2GB[line-10]);
			digitalWrite(enable2, LOW);
		}
		break;
		
	//REVISAR!! Me vuelve a pedir otro delay
	//delay(delaySeconds);		
	}
}

/*Convierte el número entero a binario y escribe las variables en el multiplexor que se le indica*/
void lineSelect(int mux[], int pinnum){
  for (int x = 0; x<5; x++){
      byte state = bitRead(pinnum, x);
      digitalWrite(mux[x], state); 
}
}

/*Apaga tanto los multiplexores como limpia los drivers.*/
void switchOff (){
lineSelect(mux1, lineOFF);
lineSelect(mux2, lineOFF);
Tlc.clear();
Tlc.update();
  }
