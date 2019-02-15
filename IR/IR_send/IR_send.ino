#include <IRremote.h>

IRsend irsend;
// ピンの接続は、必ず３番ピン

void setup()
{
}

void loop() {
	
		irsend.sendSony(0x01, 5);
	
	delay(5000); //5 second delay between each signal burst
}
