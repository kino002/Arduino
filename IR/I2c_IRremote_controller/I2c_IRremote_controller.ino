// 
#include <Wire.h>
#include <IRremote.h>

IRsend irsend;
int SLAVE_ADDRESS = 0x04;   //I2Cのアドレス『0x04』

int buf[100];
int cmd;
int count = 0;
int by;
int by2;






int khz = 38; // 38kHz carrier frequency for the NEC protocol




/*setupは起動後ときに最小に呼び出される関数でここで初期化の処理を行います*/
void setup() {
   //シリアル通信の初期化しシリアルモニタへ文字列を出力できるようにする　9600はボーレート(通信速度)
   Serial.begin(9600);

  //I2C接続を開始する 
  Wire.begin(SLAVE_ADDRESS);

  //I2Cで受信するたびに呼び出す関数を登録する
  Wire.onReceive(ReceiveMassage);

  //Serial.println("stand by OK");

}

/*setupの後、終了するまで繰り返し呼び出される関数です*/
void loop() {
  if(cmd == 0x00){
    cmd = Wire.read();
    if(cmd == 0x01){   
      Serial.println("Swich ON");
      // iresend.sendRawは、何故かloopの中でしか使えない
      irsend.sendRaw(buf, sizeof(buf) / sizeof(buf[0]), khz);
      count = 0;
      reset_buf();
    }
  }
}

/*setupの後、終了するまで繰り返し呼び出される関数です (int n)は、送られてきたデータの数*/
void ReceiveMassage(int n){

      cmd = Wire.read();
      //Serial.println(cmd);
      
      if(cmd == 0x80){
        by = Wire.read();
        //Serial.println(by);
        by2 = Wire.read();
        //Serial.println(by2);
        by = by << 8;
        buf[count] = by + by2;
              
        //Serial.println(buf[count]);

        count++; 
      }    
}

void reset_buf(){
  for (int i = 0; i < 100; i++){
    buf[i] = 0;
  }
}
