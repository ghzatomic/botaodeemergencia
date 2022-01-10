//#include <Sim800L.h>
#include <SoftwareSerial.h>

#define RX 3
#define TX 4
#define RESET 2

//Sim800L GSM(RX, TX, RESET);
#define BAUD_RATE   9600


SoftwareSerial serialGSM(RX, TX); //SIM800L Tx & Rx is connected to Arduino #3 & #2

String mensagemSocorro="ISSO E UM TESTE !!";

#define ARRAYSIZE 1
#define numeroCall1 "02114981116166" 
String results[ARRAYSIZE] = { numeroCall1 };

void setup(){
  pinMode(RESET, OUTPUT);
  digitalWrite(RESET, HIGH);
 //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  while (!Serial);  // espera a serial estabilizar
  Serial.begin(BAUD_RATE);
  
  //Begin serial communication with Arduino and SIM800L
  serialGSM.begin(BAUD_RATE);

  Serial.println("Initializing...");
  delay(1000);

  Serial.println("1");
  serialGSM.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  serialGSM.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  serialGSM.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  serialGSM.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
  Serial.println("AGUARDANDO"); 
  for (int i =0; i< ARRAYSIZE; i++) enviaSinalSocorro(results[i]);
}

void enviaSinalSocorro(String telefone){
  enviaSMS(telefone, mensagemSocorro);
  delay(1000);
  fazLigacao(telefone);
  delay(1000);
}

void enviaSMS(String telefone, String mensagem) {
  serialGSM.println("AT+CMGF=1");
  delay(1000);
  serialGSM.println("AT+CMGS=\"" + telefone + "\"\n");
  delay(1000);
  serialGSM.print(mensagem);
  delay(1000);
  serialGSM.write(26); 
  delay(1000);
  serialGSM.println("AT+CMGF=0");
  delay(1000);
  
}

void config(){
  // Mostrar operadoras : AT+COPS=?
  // Verificar se foi registrado : AT+CREG?
  //Config Claro : 
  //serialGSM.println("AT+COPS=2");
  //serialGSM.println("AT+CREG=1");
  //Config VIVO
  /*
   * AT+COPS= 4,2,"72406"
   *  AT+COPS= 4,2,"72410"
      AT+COPS= 4,2,"72411"
      AT+COPS= 4,2,"72423"
  */
}

void loop() {
  updateSerial();
  //update1();
}

void fazLigacao(String telefone) {
  serialGSM.println("ATH0\n");
  serialGSM.print((char)26); 
  serialGSM.println("ATD " + telefone + ";\n");
  serialGSM.print((char)26); 
  delay(10000);
  serialGSM.println("ATH");
  
}

void updateSerial(){
  delay(100);
  while (Serial.available()) 
  {
    serialGSM.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(serialGSM.available()) 
  {
    Serial.write(serialGSM.read());//Forward what Software Serial received to Serial Port
  }
}
