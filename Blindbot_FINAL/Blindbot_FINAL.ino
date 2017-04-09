#include "Leg.h"
#include "Body.h"
#include <SoftwareSerial.h>
#define DEFAULT_BAUD 115200
#define SOFT_RX 10
#define SOFT_TX 11

int servos[] = {0x01,0x02,0x03,
                0x04,0x05,0x07,
                0x07,0x08,0x09,
                0x10,0x11,0x12};
String message = "";
char character = '\0';
SoftwareSerial mySerial(SOFT_RX,SOFT_TX); 
//Leg leg1 = Leg(0x01,0x02,0x03, 1, Serial1, A0, 20);
Body body = Body(servos,Serial, Serial1, Serial2, Serial3);
  
void setup() {
  Serial.begin(DEFAULT_BAUD);
  Serial1.begin(DEFAULT_BAUD);
  Serial2.begin(DEFAULT_BAUD);
  Serial3.begin(DEFAULT_BAUD);


}

void loop() {
  if(mySerial.available()){
    while (character != '\n'){
       character = mySerial.read();
       message.concat(character);
       if (character == '\n'){
        /*implement me plox*/
        //command_queue.push(message);
        message = "";
        character = '\0';
       }
    }
  }

  while(true) //!command_queue.empty()
  {
    String command = command_queue.pop();
    
  }
  body.update_self();
  //leg1.update_self(false);
}

