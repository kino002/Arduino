/* set I2C library*/
#include <Wire.h>
#define ADDR1  0x64
#define forward       0x01
#define reverse       0x02




void setup(){
    Wire.begin(4, 14);      // I2Cマスター設定　SDA=IO4, SCL=IO14

}

void loop(){
    start_motor();
    delay(2000);
    reverse_motor();
    delay(2000);
    stop_motor();
    delay(2000);


}

/* ドライブモーター制御 */
void motor_func(char add , char duty){
  Wire.beginTransmission(add);
  Wire.write(0x00);
  Wire.write(duty);
  Wire.endTransmission();
}

void start_motor(){
  char i, volt;
  volt = 0x20;
  for(i=0;i<5;i++){ 
    volt = volt + ((0x40)*i);
    volt = volt | forward;
    motor_func(ADDR1 , volt);
    delay(10);
  }
}

void reverse_motor(){
    char i, volt;
  volt = 0x20;
  for(i=0;i<5;i++){ 
    volt = volt + ((0x40)*i);
    volt = volt | reverse;
    motor_func(ADDR1 , volt);
    delay(10);
  }
}

void stop_motor(){
  motor_func(ADDR1 , 0x18);
  delay(10);
  motor_func(ADDR1 , 0x1B);
  delay(10);
}
