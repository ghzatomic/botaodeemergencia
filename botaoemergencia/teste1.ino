/*#include "Sim800l.h"
#include <SoftwareSerial.h>

const byte SOFT_RX=10;   
const byte SOFT_TX=11;
const byte RST_SIM=2;

#define BAUD_RATE   9600

uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0);
 
// Objeto porta serial por software
SoftwareSerial softSerial(SOFT_RX, SOFT_TX);

char* texto = "Sensor acionado!";
char* numero = "02114981116166";




void setup() {
  pinMode(SOFT_RX, INPUT);
  pinMode(SOFT_TX, OUTPUT);
  pinMode(RST_SIM, OUTPUT);
  digitalWrite(RST_SIM, HIGH);
  while (!Serial);  // espera a serial estabilizar
   
  //Inicializa porta serial de hardware (comunicacao com o monitor)
  Serial.begin(BAUD_RATE);
 
  //Inicializa porta serial de software (comunicacao com o A6)
  softSerial.begin(BAUD_RATE);
 
  //Serial.println(F("Iniciando as portas seriais..."));
  delay(1000);
  
  
}

void updateSerial()
{ 
  while (Serial.available() != 0 )
  {
    softSerial.write(Serial.read());// redireciona entrada serial por hardware para saida serial por software
  }
  while (softSerial.available())
  {
    Serial.write(softSerial.read());// redireciona entrada serial por software para saida serial por hardware
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  updateSerial();
}



*/
