#include "Leg.h"
#include "Body.h"
#include "command_queue.h"
#define GAIT 2
#define LOCK 4
#define LEGS 1
#define BODY 3
#include <SoftwareSerial.h>
#define DEFAULT_BAUD 115200
#define SOFT_RX 10
#define SOFT_TX 11
#define COMMAND_SIZE 50

int servos[] = {0x01,0x02,0x03,
                0x04,0x05,0x07,
                0x07,0x08,0x09,
                0x10,0x11,0x12};
int message_index = 0;
char character = '\0';
SoftwareSerial mySerial(SOFT_RX,SOFT_TX); 
//Leg leg1 = Leg(0x01,0x02,0x03, 1, Serial1, A0, 20);
Body body = Body(servos,Serial, Serial1, Serial2, Serial3);
C_Queue Q = C_Queue(50);  
void setup() {
  Serial.begin(DEFAULT_BAUD);
  Serial1.begin(DEFAULT_BAUD);
  Serial2.begin(DEFAULT_BAUD);
  Serial3.begin(DEFAULT_BAUD);


}

void loop() {
  if(mySerial.available()){
    char* message = new char [COMMAND_SIZE];
    while (character != '\n'){        
       character = mySerial.read();
       message [message_index] = character;
       message_index++;
       if (character == '\n'){
        Q.enq(message);
        message = new char [COMMAND_SIZE];
        character = '\0';
       }
    }
  }

  while(Q.queue_size() != 0)
  {
    char* command = Q.deq();
    int i = 0;
    
    delete(command);
    
  }
  body.update_self();
  //leg1.update_self(false);
}
