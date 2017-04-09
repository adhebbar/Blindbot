#include <SoftwareSerial.h>
#define V_RX 10
#define V_TX 11
#define BAUD 115200

String soft_data = "";
SoftwareSerial soft_serial(V_RX, V_TX);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUD);
  Serial.println("Serial console initialized");
  soft_serial.begin(BAUD);
  Serial.println("Software serial initialized");
}

void loop() {
  if (soft_serial.available()){
    char character = soft_serial.read();
    soft_data.concat(character);
    if(character == '\n'){
      Serial.println(soft_data);
      soft_data = "";
    } 
  }
  if (Serial.available()){
    String hard_data = Serial.readStringUntil('\n');
    soft_serial.println(hard_data);
  }
}
