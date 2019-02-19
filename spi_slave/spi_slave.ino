#include <SPI.h>
 
void setup (void) {
  pinMode(MISO, OUTPUT);
  Serial.begin(9600);
 
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE1 );
  SPCR |= _BV(SPE);
  pinMode(SS, INPUT);
  SPI.attachInterrupt();
}
 
// SPI割り込み
ISR (SPI_STC_vect) {
  byte cc = SPDR; //SPDRレジスタにデータが送られてくる
  cc++;
  SPDR = cc;//SPDRレジスタにあるデータが送信される
  Serial.println(cc);
}
 
void loop (void) {
}
