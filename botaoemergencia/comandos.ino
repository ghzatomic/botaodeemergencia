//AT  Teste de Conexão


//   VELOCIDADE DA COMUNICACAO SERIAL

//AT+IPR=?  Mostra as velocidades aceitas pelo módulo
//AT+IPR=9600 Define a velocidade
//AT+IPR?   Mostra a velocidade em uso


   //DADOS DO MODULO

//AT+CGMI   Fabricante
//AT+COPS?  Operador
//AT+CGSN   IMEI
//ATI   Informações do GSM


  // SMS

//AT+CMGF=?     Modo Texto?
//AT+CMGF=1     Modo Texto
//AT+CNMI=2,2,0,0,0   Mostra Mensagens
//AT+CMGS="+5511974254932"  Envio de Mensagem     
//AT+CMGL=?     Mensagens em Memória
//AT+CMGL="ALL"     Todos os Tipos de Mensagens na Memória (Lidas, Não Lidas, ...)
//AT+CMGD=#     Apaga a mensagem de número #


  // LIGAÇÕES DE VOZ

//ATDP+5511974254932    Faz ligação para telefone
//ATA       Atender ligação
//ATH       Desligar/rejeitar ligação   
