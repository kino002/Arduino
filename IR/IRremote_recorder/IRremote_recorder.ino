// 赤外線のrawコードを得るプログラム

#include <IRremote.h>


int recvPin = 11;
IRrecv irrecv(recvPin);

int Recbuf[100];


void  setup ( )
{
  Serial.begin(9600);   
  irrecv.enableIRIn();
  Serial.println("stand by ok");  
}


void  dumpCode (decode_results *results)
{ 
  Serial.println("この赤外線機器のrawコードは、"); 
  for (int i = 1;  i < results->rawlen;  i++) {
    
    Recbuf[i] = results->rawbuf[i] * USECPERTICK;
    Serial.print(Recbuf[i]);
    Serial.print(",");
  } 
  Serial.println("");
  Serial.println("上記をコピペして");
}


void  loop ( )
{
  decode_results  results;        

  if (irrecv.decode(&results)) {  
    dumpCode(&results);           
    Serial.println("");           
    irrecv.resume();              
  }
}
