#include <IRremote.h>

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void loop() {
  if (irrecv.decode(&results)) {
    //Serial.println(results.value, HEX);
    Serial.println(results.value);  //送られてきたデータの表示
    
    Event();

    irrecv.resume(); // Receive the next value
  }
  delay(100);
}

//Event関数の中にイベントを書く
void Event(){
  if (results.value == 3412252870){
      Serial.println("LED OFF");
    }
  else if (results.value == 2574268554){
    Serial.println("LED ON");
  }
}
