#include <Wire.h>
#include "RTClib.h"

RTC_Millis rtc;

//S1302 rtc;

// CE_PIN == RST
// DATA == IO
// CLK == SCK

#define RELE_PORTA_INICIO 9
#define RELE_PORTA_FIM 13

#define ENTRADA_AGUA 13
#define ENTRADA_AGUA_RETROLAVAGEM 12
#define ENTRADA_AGUA_CAIXA_DAGUA 11
#define EXPURGO_AGUA 10
#define MOTOBOMBA 9

#define TEMPO_RETROLAVAGEM 30

void setup() {
  Serial.begin(57600);
  Serial.print("Iniciando prototipo: ");
  Serial.print(__DATE__);
  Serial.print(" ");
  Serial.println(__TIME__);
  rtc.begin(DateTime(__DATE__, "00:01:01"));
  Serial.print("Habilitando portas de RELE inicio: ");
  Serial.print(RELE_PORTA_INICIO);
  Serial.print(" Fim: ");
  Serial.println(RELE_PORTA_FIM);
  for(int i = RELE_PORTA_INICIO; i <= RELE_PORTA_FIM; i++) {
    Serial.print("Iniciando porta como Saida: ");
    Serial.println(i);
    pinMode(i,OUTPUT);
  }
  digitalWrite(ENTRADA_AGUA,HIGH);
  digitalWrite(ENTRADA_AGUA_CAIXA_DAGUA, HIGH);
  digitalWrite(MOTOBOMBA,HIGH);
  
}

void loop() {
  // put your main code here, to run repeatedly:
    DateTime now = rtc.now();
/*    char buf[100];
    strncpy(buf,"DD.MM.YYYY  hh:mm:ss\0",100);
    Serial.println(now.format(buf)); */
/*  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println(); */
    
  if(now.second() == 0) {
    Serial.println("INICIANDO CICLO DE RETROLAVAGEM");
    digitalWrite(ENTRADA_AGUA,LOW);
    digitalWrite(ENTRADA_AGUA_CAIXA_DAGUA, LOW);
    //delay(5000);
    digitalWrite(ENTRADA_AGUA_RETROLAVAGEM,HIGH);
    digitalWrite(EXPURGO_AGUA,HIGH);
    delay(TEMPO_RETROLAVAGEM*1000);
    Serial.println("VOLTANDO PARA CICLO NORMAL");
    digitalWrite(ENTRADA_AGUA_RETROLAVAGEM,LOW);
    digitalWrite(EXPURGO_AGUA,LOW);
    
    digitalWrite(ENTRADA_AGUA,HIGH);
    digitalWrite(ENTRADA_AGUA_CAIXA_DAGUA, HIGH);  
  }
    
  delay(1000);
}
