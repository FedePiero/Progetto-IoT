#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2,3);

void setup(){
  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop(){
  if(BTSerial.available()){
    Serial.write(BTSerial.read());
  }
  delay(100);
  if(Serial.available()){
    BTSerial.write(Serial.read());
  }
}
