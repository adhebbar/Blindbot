#include "Leg.h"
#include "Robot.h"
#include "utility_functions.h"
#include "A1_16.h"
//Implementation
//Constructor
Leg::Leg(int cox_servo, int femur_servo, int tibia_servo, int leg_ID, 
			  HardwareSerial& serial, const uint8_t softpot_pin, int force_pin,
			  bool inverted_cox, bool inverted_femur, bool inverted_tibia):
myserial(serial)
{
	this->cox_servo = cox_servo;
	this->femur_servo = femur_servo;
	this->tibia_servo = tibia_servo;
	this->leg_ID = leg_ID;
	this->softpot_pin = softpot_pin;
	this->force_pin = force_pin;
  this->inverted_cox = inverted_cox;
  this->inverted_femur = inverted_femur;
  this->inverted_tibia = inverted_tibia;
}

void Leg::FK (float answer[], bool debug_prints){
  int cox_angle = ReadPosition(cox_servo)*360/1024;
  int femur_angle = ReadPosition(femur_servo)*360/1024;
  int tibia_angle = ReadPosition(tibia_servo)*360/1024; //double check this conversion
  float x = COX_LEN + FEMUR_LEN*cos(femur_angle) + 
            TIBIA_LEN*cos(90-femur_angle-tibia_angle);
  float y = FEMUR_LEN*sin(femur_angle) + TIBIA_LEN*cos(90-femur_angle-tibia_angle);
  float z = x*tan(cox_angle);
  answer[0] = x;
  answer[1] = y;
  answer[2] = z;
  if (debug_prints){
    print_val("x: ", x);
    print_val("y: ", y);
    print_val("z: ", z);
  }
}

void Leg::FK(bool debug_prints){
  int cox_angle = ReadPosition(cox_servo)*360/1024;
  int femur_angle = ReadPosition(femur_servo)*360/1024;
  int tibia_angle = ReadPosition(tibia_servo)*360/1024; //double check this conversion
  float x = COX_LEN + FEMUR_LEN*cos(femur_angle) + 
            TIBIA_LEN*cos(90-femur_angle-tibia_angle);
  float y = FEMUR_LEN*sin(femur_angle) + TIBIA_LEN*cos(90-femur_angle-tibia_angle);
  float z = x*tan(cox_angle);
  current_x = x;
  current_y = y;
  current_z = z;
}


void Leg::update_force(){
  force_val = analogRead(force_pin);
}

void Leg::update_soft(){
  soft_val = analogRead(softpot_pin);
}

void Leg::update_self(bool debug_prints){
  update_force();
  update_soft();
  update_angles();
  FK(debug_prints);
}

/* POSITION RELATED */

//updates the current position of the legs
void Leg::set_position(float x, float y, float z){
	current_x = x;
	current_z = z;
	current_y = y;
}

//updates the array with the current position values
void Leg::get_position(float result[]){
	result[0] = current_x;
	result[1] = current_y;
	result[2] = current_z;
}

/*

*/
void Leg::IK (float x, float y, float z, float answer[], 
			  bool debug_prints, bool update)
{
   float cox_angle = atan2(z,x);
   if (cox_angle > MAX_COX)
    return;
   float L = sqrt(x*x+z*z);
   float HF = sqrt(y*y + (L - COX_LEN)*(L-COX_LEN));
   float alpha1 = atan2((L-COX_LEN),y);
   float alpha2 = acos((HF*HF + FEMUR_LEN*FEMUR_LEN - TIBIA_LEN*TIBIA_LEN)/(2*HF*FEMUR_LEN));
   float femur_angle = pi/2.0 - (alpha1 + alpha2); 
   float beta_denom = (2.0*FEMUR_LEN*TIBIA_LEN);
   float beta_num = FEMUR_LEN*FEMUR_LEN+TIBIA_LEN*TIBIA_LEN-HF*HF;
   float beta = acos(beta_num/beta_denom);
   if(debug_prints){
	   print_val("HF ", HF);
	   print_val("Alpha 1 ", alpha1);
	   print_val("Alpha 2 ", alpha2);
	   print_val("beta_denom ", beta_denom); 
	   print_val("beta_num ", beta_num);
	   print_val("Beta ", beta);
	}
   float tibia_angle = beta;
   if (y < 0){
      tibia_angle += pi;
   }
   answer[0] = convert_angle(cox_angle);
   answer[1] = convert_angle(femur_angle);
   answer[2] = convert_angle(tibia_angle,0.0, 2*pi);
   if(update)
   {
		set_position(x,y,z);
		move_to_angles(answer[0], answer[1], answer[2]);
   }
   if (debug_prints){
        print_val("Coxa ",cox_angle);
        print_val("Femur ", femur_angle);
        print_val("Tibia ",tibia_angle);
   }
}

/*   */

void Leg::normal_foot(int pos, int playtime){
  int theta_1 = pos - 512;
  int theta_2 = 230 + theta_1;
  A1_16_SetPos_serial(tibia_servo, CMD_I_JOG, playtime, theta_2, myserial);
}

/* ANGLE RELATED */

void Leg::get_angles(int answer[]){
	answer[0] = cox_angle;
	answer[1] = femur_angle;
	answer[2] = tibia_angle;
}

void Leg::update_angles(){
  this->cox_angle = ReadPosition_serial(cox_servo, myserial);
	this->femur_angle = ReadPosition_serial(femur_servo, myserial);
	this->tibia_angle = ReadPosition_serial(tibia_servo, myserial);
}

//Moves the leg to the desired angles
void Leg::move_to_angles(int angle1, int angle2, int angle3){
  if(this->inverted_cox)
     angle1 = map(angle1,0,1024,1024,0);
  if(this->inverted_femur)
     angle2 = map(angle2,0,1024,1024,0);
  if(this->inverted_tibia)   
     angle3 = map(angle3,0,1024,1024,0);
	if(angle1 != -1) cox_angle = angle1;
	if(angle2 != -1) femur_angle = angle2;
	if(angle3 != -1) tibia_angle = angle3;
	if(angle1 != -1) A1_16_SetPos_serial(cox_servo, CMD_I_JOG,0x20, angle1, myserial);
	if(angle2 != -1) A1_16_SetPos_serial(femur_servo, CMD_I_JOG,0x20, angle2, myserial);
	if(angle3 != -1) A1_16_SetPos_serial(tibia_servo, CMD_I_JOG,0x20, angle3, myserial);
}

/* SENSOR RELATED */
int Leg::get_force(){
	return force_val;
}

int Leg::get_soft(){
	return soft_val;
}

/* COMMUNICATION RELATED */

void Leg::print_angles(bool update){
	if (update)
		update_angles();
	print_val("Coxa: ",cox_angle);
	print_val("Femur : ",femur_angle);
	print_val("Tibia : ",tibia_angle);
}

void Leg::print_position(bool update){
	if (update)
		FK(false);
	print_val("X: ", current_x);
	print_val("Y: ", current_y);
	print_val("Z: ", current_z);
}

void Leg::acknowledge(){
	print_val("ID: ", leg_ID);
}
