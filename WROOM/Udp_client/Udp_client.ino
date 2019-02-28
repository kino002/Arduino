#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#ifndef STASSID
#define STASSID "taka2"               // SSID
#define STAPSK  "hashi222"            // SSIDパスワード
#endif

unsigned int localPort = 50000;      // 送受信するポート番号

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //　受信したデータを保存する配列

char send_IP_addr[] = "192.168.10.126";   // 送り先のIPアドレス



WiFiUDP Udp;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);
}

void loop() {
    udp_rcv();                // 受信関数
    
    udp_send("届いたかな？");   // ()の中には送信する文字
    // udp_send(packetBuffer);    // 受信した文字列をそのまま返す

    delay(10);                // 送受信を安定させるために
}

void udp_rcv() {
  int packetSize = Udp.parsePacket();
  if (packetSize) {                           // もし受信したら
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = Udp.remoteIP();
    for (int i = 0; i < 4; i++) {
      Serial.print(remote[i], DEC);
      if (i < 3) {
        Serial.print(".");
      }
    }
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    for (int i = 0; i < UDP_TX_PACKET_MAX_SIZE; i++){ 
      packetBuffer[i] = NULL;   // 配列を初期化
    }    
    
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);   // データを受信
    Serial.println("Contents:");
    Serial.println(packetBuffer);
  }    
}

void udp_send(char data[]){
    Udp.beginPacket(Udp.remoteIP(), localPort); // 送信元に送り返す
    //Udp.beginPacket(send_IP_addr, localPort); // 指定したIPアドレスに送る
    Udp.write(data);
    Udp.endPacket(); 
}
