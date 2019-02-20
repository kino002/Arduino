#include <SPI.h>
 
void setup (void) {
  pinMode(MISO, OUTPUT);
  Serial.begin(9600);
 
  SPI.setBitOrder(MSBFIRST);    // 入出力のビットオーダー設定
  SPI.setDataMode(SPI_MODE1 );  // 通信モード設定
  SPCR |= _BV(SPE);             // SPI Enable
  pinMode(SS, INPUT);
  SPI.attachInterrupt();  // SPI割り込み開始
}
 
// SPI割り込み
ISR (SPI_STC_vect) {
  // SPDRレジスタを入れ物としてデータの送受信を行う
  byte cc = SPDR; //SPDRレジスタにデータが送られてくる
  if(cc == 78){
    // 処理を書く
    Serial.println("Hello World");
  }
  // ここでSPDRに書き込まなければ、何も送信されない。
  SPDR = 55;//SPDRレジスタにあるデータが送信される
}
 
void loop (void) {
}
