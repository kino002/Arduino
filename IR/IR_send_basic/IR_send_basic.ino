#include <IRremote.h>

IRsend irsend;    // 赤外線出力設定　接続ピンはD3ピン

void setup()
{
}

void loop() {
	for (int i = 0; i < 3; i++) {   // 0.04秒で3回繰り返す
		irsend.sendSony(70, 16);   // ソニー形式で「70」を16bitで送信
		delay(40);
	}
	delay(5000);    // 5秒待つ
}
