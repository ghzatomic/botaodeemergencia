#include <Sim800l.h>
#include <SoftwareSerial.h>
Sim800l Sim800l;

char* texto = "Sensor acionado!";
char* numero = "02114981116166";




void setup() {
  Serial.begin(9600);
  Sim800l.begin(); // initializate the library.
  Serial.println("Sensor acionado! Enviando SMS...");
  Sim800l.sendSms(numero, texto);
  Serial.println("SMS Enviado...");
}



void loop() {
  // put your main code here, to run repeatedly:

}
