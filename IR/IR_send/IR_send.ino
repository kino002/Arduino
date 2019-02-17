#include <IRremote.h>

IRsend irsend;

int khz = 38; // 38kHz carrier frequency for the NEC protocol
int a[3] = {3500, 1500, 600}
int b[3] = {4000, 2000, 1200}

/*setupは起動後ときに最小に呼び出される関数でここで初期化の処理を行います*/
void setup() {
   //シリアル通信の初期化しシリアルモニタへ文字列を出力できるようにする　9600はボーレート(通信速度)
   Serial.begin(9600);
}

/*setupの後、終了するまで繰り返し呼び出される関数です*/
void loop() {
  soushin(a);
}

void soushin(int buf[100]){
  irsend.sendRaw(buf, sizeof(buf) / sizeof(buf[0]), khz);
}