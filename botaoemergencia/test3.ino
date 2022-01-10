/*

#include "Sim800l.h"
#include <SoftwareSerial.h>

#define RX 10
#define TX 11
#define RESET 2

#define BAUD_RATE   9600
#define pinBotaoCall 12
#define senhaGsm "1234"
bool callStatus = false;

bool temSMS = false;
String telefoneSMS;
String dataHoraSMS;
String mensagemSMS;
String comandoGSM = "";
String ultimoGSM = "";

SoftwareSerial serialGSM(RX, TX); //SIM800L Tx & Rx is connected to Arduino #3 & #2



#define numeroCall "981116166" 

void configuraGSM();

void setup(){
 //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  serialGSM.begin(9600);

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
  delay(2000);
  Serial.println("AGUARDANDO"); 

}

void loop() {
  updateSerial();
  //update1();
}


void update1(){
  leGSM();

  if (comandoGSM != "") {
      Serial.println(comandoGSM);
      ultimoGSM = comandoGSM;
      comandoGSM = "";
  }

  if (temSMS) {

     Serial.println("Chegou Mensagem!!");
     Serial.println();
    
     Serial.print("Remetente: ");  
     Serial.println(telefoneSMS);
     Serial.println();
    
     Serial.print("Data/Hora: ");  
     Serial.println(dataHoraSMS);
     Serial.println();
    
     Serial.println("Mensagem:");  
     Serial.println(mensagemSMS);
     Serial.println();
      
     mensagemSMS.trim();      
     if ( mensagemSMS == senhaGsm ) {
        Serial.println("Enviando SMS de Resposta.");  
         enviaSMS(telefoneSMS, "SMS Recebido e Senha OK!");
     }
     temSMS = false;
  }

  if (!digitalRead(pinBotaoCall) && !callStatus) {
     Serial.println("Afetuando Ligacao..."); 
     fazLigacao(numeroCall);
     callStatus = true;
  }

  if (ultimoGSM.indexOf("+COLP:") > -1) {
     Serial.println("LIGACAO EM ANDAMENTO");
     ultimoGSM = "";                
  }
       
  if (ultimoGSM.indexOf("NO CARRIER") > -1) {
     Serial.println("LIGACAO TERMINADA");
     ultimoGSM = "";
     callStatus = false;
  }
       
  if (ultimoGSM.indexOf("BUSY") > -1) {
     Serial.println("LINHA/NUMERO OCUPADO");
     ultimoGSM = "";
     callStatus = false;
  }

  if (ultimoGSM.indexOf("NO DIALTONE") > -1) {
     Serial.println("SEM LINHA");
     ultimoGSM = "";
     callStatus = false;
  }
       
  if (ultimoGSM.indexOf("NO ANSWER") > -1) {
     Serial.println("NAO ATENDE");
     ultimoGSM = "";
     callStatus = false;
  }
}

char* toChar(String ret){
  char* buf = (char*) malloc(sizeof(char)*ret.length()+1);
  ret.toCharArray(buf, ret.length()+1);
  return buf;
}

void configuraGSM() {
   serialGSM.print("AT+CMGF=1\n;AT+CNMI=2,2,0,0,0\n;ATX4\n;AT+COLP=1\n"); 
}

void enviaSMS(String telefone, String mensagem) {
  serialGSM.print("AT+CMGS=\"" + telefone + "\"\n");
  serialGSM.print(mensagem + "\n");
  serialGSM.print((char)26); 
}

void fazLigacao(String telefone) {
  serialGSM.println("ATH0\n");
  serialGSM.print((char)26); 
  serialGSM.println("ATD " + telefone + ";\n");
  serialGSM.print((char)26); 
}

void leGSM()
{
  static String textoRec = "";
  static unsigned long delay1 = 0;
  static int count=0;  
  static unsigned char buffer[64];

  if (serialGSM.available()) {            
 
     while(serialGSM.available()) {         
   
        buffer[count++] = serialGSM.read();     
        if(count == 64)break;
     }

     textoRec += (char*)buffer;
     delay1   = millis();
     
     for (int i=0; i<count; i++) {
         buffer[i]=NULL;
     } 
     count = 0;                       
  }


  if ( ((millis() - delay1) > 100) && textoRec != "" ) {

     if ( textoRec.substring(2,7) == "+CMT:" ) {
        temSMS = true;
     }

     if (temSMS) {
            
        telefoneSMS = "";
        dataHoraSMS = "";
        mensagemSMS = "";

        byte linha = 0;  
        byte aspas = 0;
        for (int nL=1; nL < textoRec.length(); nL++) {

            if (textoRec.charAt(nL) == '"') {
               aspas++;
               continue;
            }                        
          
            if ( (linha == 1) && (aspas == 1) ) {
               telefoneSMS += textoRec.charAt(nL);
            }

            if ( (linha == 1) && (aspas == 5) ) {
               dataHoraSMS += textoRec.charAt(nL);
            }

            if ( linha == 2 ) {
               mensagemSMS += textoRec.charAt(nL);
            }

            if (textoRec.substring(nL - 1, nL + 1) == "\r\n") {
               linha++;
            }
        }
     } else {
       comandoGSM = textoRec;
     }
     
     textoRec = "";  
  }     
}

void updateSerial(){
  //Serial.println("UPDATE ... ");
  delay(500);
  while (Serial.available()) 
  {
    serialGSM.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(serialGSM.available()) 
  {
    Serial.write(serialGSM.read());//Forward what Software Serial received to Serial Port
  }
}





*/
