#include "Leg.h"
#include "Body.h"
#include "command_queue.h"
#include "Robot.h"
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
                        0x0A,0x0B,0x0C};
int message_index = 0;
char character = '\0';
SoftwareSerial mySerial(SOFT_RX,SOFT_TX); 
//Leg leg1 = Leg(0x01,0x02,0x03, 1, Serial1, A0, 20,true, false, true);
//Leg leg2 = Leg(0x04,0x05,0x06, 1, Serial1, A0, 20, true, true, false);
//Leg leg3 = Leg(0x07,0x08,0x09, 1, Serial1, A0, 20, false, false, true);
//Leg leg4 = Leg(0x0A,0xB,0x0C, 1, Serial1, A0, 20, false, true, true);
Body body = Body(servos,Serial, Serial1, Serial2, Serial3);
C_Queue Q = C_Queue(50);    
void setup() {
    Serial.begin(DEFAULT_BAUD);
    Serial1.begin(DEFAULT_BAUD);
    Serial2.begin(DEFAULT_BAUD);
    Serial3.begin(DEFAULT_BAUD);
    //delay(5000);
    float answer[3];
    //delay(500);
    //leg1.IK(17.0, 2.0, 10.0, answer, 
    //    false, true);
    //leg2.IK(17.0, 2.0, -10.0, answer, 
    //    false, true);
    //delay(500);
    //leg3.IK(17.0, 2.0, -10.0, answer, 
    //   true, true);
    //delay(500);
    //leg4.IK(23.0, 0.0, 0, answer, 
    //    false, true);
    //delay(5000);
    test();
    //leg3.IK(14,0,-5,answer, true, true);
}

void loop() {
    //leg4.print_angles(true);
    //leg4.move_to_angles(512,768,256);
    //angle == 512 ? angle = 1024: angle = 512;
    delay(1000);
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
    //body.update_self();
    //leg1.update_angles();
}

void test(){
    body.set_position_leg(0, 17.0, 2.0, 10.0);
    delay(100);
    body.set_position_leg(1, 17.0, 2.0, -10.0);
    delay(100);
    body.set_position_leg(2, 17.0, 2.0, -10.0);
    delay(100);
    body.set_position_leg(3, 17.0, 2.0, 10.0);
    delay(2000);
    body.set_position_leg(0, 10.0, 5.0, 10.0);
    delay(100);
    body.set_position_leg(1, 10.0, 5.0, -10.0);
    delay(100);
    body.set_position_leg(2, 10.0, 5.0, -10.0);
    delay(100);
    body.set_position_leg(3, 10.0, 5.0, 10.0);
    delay(3000);
    //body.set_position_leg(0, COX_LEN+FEMUR_LEN, -TIBIA_LEN ,0.0);
    //body.set_position_leg(1, COX_LEN+FEMUR_LEN, -TIBIA_LEN ,0.0);
    //body.set_position_leg(2, COX_LEN+FEMUR_LEN, -TIBIA_LEN ,0.0);
    //body.set_position_leg(3, COX_LEN+FEMUR_LEN, -TIBIA_LEN ,0.0);
    delay(3000);
}
