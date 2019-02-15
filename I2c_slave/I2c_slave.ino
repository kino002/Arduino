#include <Wire.h>

int SLAVE_ADDRESS = 0x04;   //I2Cのアドレス『0x04』
byte buf[50];
int cmd = 0;
byte lists[] = {'F', 'G', 'H', 'I', 'J'};
char ch;

/*setupは起動後ときに最小に呼び出される関数でここで初期化の処理を行います*/
void setup() {
   //シリアル通信の初期化しシリアルモニタへ文字列を出力できるようにする　9600はボーレート(通信速度)
   Serial.begin(9600);

  //I2C接続を開始する 
  Wire.begin(SLAVE_ADDRESS);

  //I2Cで受信するたびに呼び出す関数を登録する
  Wire.onReceive(ReceiveMassage); 

  //I2Cでリクエストを受信したときに呼び出す関数を登録する 
  Wire.onRequest(RequestMassage);
}

/*setupの後、終了するまで繰り返し呼び出される関数です*/
void loop() {
}

/*setupの後、終了するまで繰り返し呼び出される関数です (int n)は、送られてきたデータの数*/
void ReceiveMassage(int n){

  // cmdを受信
  cmd = Wire.read();
 
  // cmd = 0x80ならデータが送られてきているので受信処理を行う
  if(cmd == 0x80){
    // 何かする
    // 全データ受信だけしてみるならこんな感じ
    for(int i = 0; i < n-1; i++){
      buf[i] = Wire.read();
      ch = buf[i];
      Serial.println(ch);
    }
  }
}

//リクエスト要求を受けたときにlists[i]を送信する。
void RequestMassage(){
  for(int i = 0; i < 6; i++){
    Wire.write(lists[i]);
  }
}
