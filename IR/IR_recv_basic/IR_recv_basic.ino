#include <IRremote.h>


int RECV_PIN = 11;        // デジタル11ピン

IRrecv irrecv(RECV_PIN);  // 赤外線入力ピン設定

decode_results results;   // 受信したデータ


void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();            // 受信開始
  Serial.println("stand by OK!");
}

void loop() {
  if (irrecv.decode(&results)) {    // 受信したデータがresultsに入ると
    Serial.println(results.value);
    if (results.value == 70){       // results.valueと送られてきたデータを比較
      // ここに処理を書く
      Serial.println("Hello IR");
    }
    irrecv.resume();                // 受信終了
  }
  delay(100);
}
