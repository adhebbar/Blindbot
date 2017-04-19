#ifndef _LEG_H_
#define _LEG_H_
#include "Arduino.h"

class Leg{
	int cox_angle, femur_angle, tibia_angle;
	int cox_servo, femur_servo, tibia_servo;
	int leg_ID, gait_step;
	int force_pin, softpot_pin;
	int force_val, soft_val;
  bool inverted_cox, inverted_femur, inverted_tibia;
	public:
		HardwareSerial& myserial;
    Leg(HardwareSerial& serial): myserial(serial){}
    Leg(int cox_servo, int femur_servo, int tibia_servo, int leg_ID, 
       HardwareSerial& serial, const uint8_t softpot_pin, int force_pin,
       bool inverted_cox, bool inverted_femur, bool inverted_tibia);
		float current_x, current_y, current_z;
		void set_position(float x, float y, float z);
		void get_position(float result[]);
		void move_to_position(float x, float y, float z);
		void IK(float x, float y, float z, float answer[], 
			    bool debug_prints, bool update);
		void FK(bool debug_prints);
    void FK (float answer[], bool debug_prints);
		void normal_foot(int pos, int playtime);
		void move_to_angles(int angle1, int angle2, int angle3);
		void get_angles(int answer[]);
    void acknowledge();
		void update_angles();	
		void update_force();
		void update_soft();
		void update_self(bool debug_prints); //updates all the values
		void rotate_frame(); //might or might not need this
    void print_position(bool update);
    void print_angles(bool update);
    int get_soft();
    int get_force();
};
#endif
