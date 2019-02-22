#include <Arduino.h>

/*
   Original Code by pcbt: https://github.com/pcbt/excelitas-digipyro2-arduino
   ported to esp32.
 */

#define SERIAL 22
#define DL 23

void writeregval(int pin1,unsigned long regval){
  int i;
  int _pin1=pin1;
  unsigned long _regval=regval;
  unsigned char nextbit;
  unsigned long regmask = 0x1000000;
  pinMode(_pin1,OUTPUT);
  digitalWrite(_pin1,LOW);
  for(i=0; i < 25; i++) {
    nextbit = (_regval&regmask)!=0;
    regmask >>=1;
    digitalWrite(_pin1,LOW);
    digitalWrite(_pin1,HIGH);

    if(nextbit) {
            digitalWrite(_pin1,HIGH);
            Serial.print("1");
    }
    else{
            digitalWrite(_pin1,LOW);
            Serial.print("0");
    }
    delayMicroseconds(100);
  }
  Serial.print("\ndone\n");
  digitalWrite(_pin1,LOW);
  delayMicroseconds(600);
}

void setup() {
  Serial.begin(115200);
  pinMode(SERIAL,OUTPUT);
  pinMode(DL,INPUT);

  Serial.println("Writing to register");
  delay(1000);

  //see https://media.digikey.com/pdf/Data%20Sheets/Excelitas%20PDFs/PYQ1648-7052.pdf
  // | 8bit sensitivity | 4bit blind time | 2bit pulse counter | 2bit window time | 2bit operatin mode | 2bit filter source | 5bit reserved |
  //00011000 0010 01 10 10 00 10000
  writeregval(SERIAL,0x00304D10);
  i=0;
}

void loop() {
  int movement = digitalRead(DL);
  if(movement) {
  Serial.println(movement);
  Serial.println("movement");
  pinMode(DL,OUTPUT);
  digitalWrite(DL,LOW);
  delay(2000);
  pinMode(DL,INPUT);
  }
}
