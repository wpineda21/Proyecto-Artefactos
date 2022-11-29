//-----------------------------
//Uses no library :-)
//-----------------------------

// Programa : Detector de cores usando modulo TCS230  
// Alteracoes e comentarios : Arduino e Cia  
//  
// Baseado no programa original de Martin Mason  
#include <Servo.h>
#define LED 8
//Pinos de conexao do modulo TCS230  
const int s0 = 6;  
const int s1 = 5;  
const int s2 = 4;  
const int s3 = 3;  
const int out = 2;
int entrada1 = 11;
int entrada2 = 12;
int entrada3 = 10;
int entrada4 = 7;
int enableA = 13;   
int pulsador=11;
Servo servoMotor; 
   
//Pinos dos leds    
//int pinoledverm = 11;   //You may ignore this. Unused unless you want to light LEDs
//int pinoledverd = 7;   //You may ignore this. Unused unless you want to light LEDs 
//int pinoledazul = 10;   //You may ignore this. Unused unless you want to light LEDs 
    
//Variaveis que armazenam o valor das cores  
int red = 0;  
int green = 0;  
int blue = 0;  
    
void setup()   
{  
  pinMode(entrada1, OUTPUT);
  pinMode(entrada2, OUTPUT);
  pinMode(entrada3, OUTPUT);
  pinMode(entrada4, OUTPUT);
  //pinMode(enableA, OUTPUT);
  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(out, INPUT);  
//  pinMode(pinoledverm, OUTPUT);  
//  pinMode(pinoledverd, OUTPUT);  
//  pinMode(pinoledazul, OUTPUT);  
  Serial.begin(9600);  
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, HIGH); 
     pinMode(LED,OUTPUT);
   digitalWrite(LED,LOW);
      servoMotor.attach(9);//el  pin 9 es utilizado EXCLUSIVO Para servomotor
   pinMode(pulsador, INPUT);
}  
    
void loop() 
{  
  
  int pulsador2 = digitalRead(pulsador);
  
  if (pulsador2){
    digitalWrite(LED,LOW);
  }else{
    digitalWrite(LED,LOW);
  }
     
  color(); //Chama a rotina que le as cores  
  //Mostra no serial monitor os valores detectados  
  Serial.print("Red :");  
  Serial.print(red, DEC);  
  Serial.print(" Green : ");  
  Serial.print(green, DEC);  
  Serial.print(" Blue : ");  
  Serial.print(blue, DEC);  
  Serial.println();  

  delay(2000);

  //Verifica se a cor vermelha foi detectada  
  if (red < blue && red < green && red > 50)  
  {  
   Serial.println("Red");  
//   digitalWrite(pinoledverm, HIGH); //Acende o led vermelho  
//   digitalWrite(pinoledverd, LOW);  
//   digitalWrite(pinoledazul, LOW);  
  }  

  //Verifica se a cor azul foi detectada  
  else if (blue < red && blue < green)   
  {  
  digitalWrite(entrada1, HIGH);
  digitalWrite(entrada2, LOW);
  analogWrite(enableA, 128);
  delay(100);
  digitalWrite(entrada1, LOW);
  digitalWrite(entrada2, LOW);

   servoMotor.write(0);  
      // Esperamos 1 segundo
    delay(1000);
      
      // Desplazamos a la posición 90º
      //servoMotor.write(90);
      // Esperamos 1 segundo
      //delay(1000);
      
      // Desplazamos a la posición 180º
      servoMotor.write(60);
      // Esperamos 1 segundo
      delay(1000);

        servoMotor.write(100);  
      // Esperamos 1 segundo
      //delay(1000); 
   Serial.println("Blue");  
  
  digitalWrite(entrada2, HIGH);
  digitalWrite(entrada1, LOW);
  analogWrite(enableA, 128);
  delay(100);
  digitalWrite(entrada1, LOW);
  digitalWrite(entrada2, LOW);
  
 //  digitalWrite(pinoledverm, LOW);  
 // digitalWrite(pinoledverd, LOW);  
 //  digitalWrite(pinoledazul, HIGH); //Acende o led azul  
 
  }  

  //Verifica se a cor verde foi detectada  
  else if (green < red && green < blue)  
  {  
  digitalWrite(entrada3, LOW);
  digitalWrite(entrada4, HIGH);
  analogWrite(enableA, 128);
  delay(100);
  digitalWrite(entrada3, LOW);
  digitalWrite(entrada4, LOW);
      servoMotor.write(0);  
      // Esperamos 1 segundo
      delay(1000);
      
      // Desplazamos a la posición 90º
      //servoMotor.write(90);
      // Esperamos 1 segundo
      //delay(1000);
      
      // Desplazamos a la posición 180º
      servoMotor.write(60);
      // Esperamos 1 segundo
      delay(1000);
      servoMotor.write(100);  
      // Esperamos 1 segundo
      //delay(1000);
   Serial.println("Green");  
 
  digitalWrite(entrada4, LOW);
  digitalWrite(entrada3, HIGH);
  analogWrite(enableA, 128);
  delay(1000);
  digitalWrite(entrada3, LOW);
  digitalWrite(entrada4, LOW);
  }  
  Serial.println();  

  //Aguarda 2 segundos, apaga os leds e reinicia o processo  
  delay(500);   
 // digitalWrite(pinoledverm, LOW);  
 // digitalWrite(pinoledverd, LOW);  
 // digitalWrite(pinoledazul, LOW);  
 }  
    
void color()  
{  
  //Rotina que le o valor das cores  
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);  
  //count OUT, pRed, RED  
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);  
  //count OUT, pBLUE, BLUE  
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);  
  //count OUT, pGreen, GREEN  
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
}
