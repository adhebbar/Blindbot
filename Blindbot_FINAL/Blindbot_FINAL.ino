#include "Leg.h"
#include <SoftwareSerial.h>
#define DEFAULT_BAUD 115200
#define SOFT_RX 10
#define SOFT_TX 11

int servos[] = {0x01,0x02,0x03,
                0x04,0x05,0x07,
                0x07,0x08,0x09,
                0x10,0x11,0x12};
SoftwareSerial mySerial(SOFT_RX,SOFT_TX); 
Leg leg1 = Leg(0x01,0x02,0x03, 1, Serial1, A0, 20);

void setup() {
  Serial.begin(DEFAULT_BAUD);
  Serial1.begin(DEFAULT_BAUD);
  Serial2.begin(DEFAULT_BAUD);
  Serial3.begin(DEFAULT_BAUD);
  //Body body = Body(servos,Serial, Serial1, Serial2, Serial3);
  float answer[3];
  leg1.IK(21.0, 4.0, 0.0, answer, true, true);
  delay(2000);
  leg1.IK(16.0, 8.0, 0.0, answer, true, true);
  delay(2000);
  leg1.IK(23.0, 0.0, 0.0, answer, true, true);
  delay(2000);
  leg1.IK(2.0, 4.0, 0.0, answer, true, true);

}

void loop() {
  if(mySerial.available()){
    String message = mySerial.readStringUntil('\n');
    
  }
  //body.update();
  leg1.update_self(false);
}

void message(String& message){
  return;
}

