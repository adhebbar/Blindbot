#include "Body.h"
#include "Robot.h"
#include "A1_16.h"
#include "BOLIDE_Player.h"
#include "utility_functions.h"
#include "Leg.h"
#include "Arduino.h"

/* IMPLEMENTATION */

Body::Body(int* servos, HardwareSerial& serial, HardwareSerial& serial1, 
		   HardwareSerial& serial2, HardwareSerial& serial3):
legs({{int(servos[3*0]),int(servos[1+3*0]),int(servos[2+3*0]), 0, serial, A0, 0},
      {int(servos[3*1]),int(servos[1+3*1]),int(servos[2+3*1]), 1, serial1, A0, 0},
      {int(servos[3*2]),int(servos[1+3*2]),int(servos[2+3*2]), 2, serial2, A0, 0}, 
      {int(servos[3*3]),int(servos[1+3*3]),int(servos[2+3*3]), 3, serial3, A0, 0}})
{
	this->locked = false;
	/*for (int i = 0; i < 4; i ++){
		switch(i){
			case 0: legs[i] = Leg();
			case 1: legs[i] = Leg(int(servos[3*i]),int(servos[1+3*i]),int(servos[2+3*i]), int(i), serial1, A0, 0);
			case 2: legs[i] = Leg(int(servos[3*i]),int(servos[1+3*i]),int(servos[2+3*i]), int(i), serial2, A0, 0);
			case 3: legs[i] = Leg(int(servos[3*i]),int(servos[1+3*i]),int(servos[2+3*i]), int(i), serial3, A0, 0);
		}
	}*/
	update_self();
}

void Body::update_self(){
    float coord_buff[3];
    if (!locked) gait_next();
    //read_IMU();
    for (int i = 0; i < num_legs; i++){
        legs[i].update_self(false);
        legs[i].get_position(coord_buff);
        x_coords[i] = coord_buff[0];
        y_coords[i] = coord_buff[1];
        z_coords[i] = coord_buff[2];
    }
    //calculate_tilt();
}

/* KINEMATICS RELATED */

void Body::update_COM(){
    float forces[3];
    for (int i = 0; i < num_legs; i++){
        forces[i] = convert_force(legs[i].get_force());
    }
    convert_to_kg(forces,num_legs);
    float center_x;
    float center_y;
    float mass_sum = 0;
    for (int j = 0; j < num_legs; j ++){
        mass_sum += forces[j];
        center_x += forces[j]*x_coords[j];
        center_y += forces[j]*y_coords[j];
    }
    cx = center_x;
    cy = center_y;
    cz = 0;
}

void Body::balance(){

}

/* MOVEMENT */

//Rotate in place around y axis
void Body::rotate_y(int d_theta){
    Leg reference = legs[1];
    float x0 = reference.current_x + XOFF;
    float z0 = reference.current_z + YOFF;
    float R = sqrt(x0*x0 + z0*z0);
    float alpha = tan(z0/x0);
    float x1 = sqrt((R*R)/(1+tan(alpha+d_theta)*tan(alpha+d_theta)));
    float z1 = sqrt(R*R - x1*x1);
    return x1, z1; //New coords for leg
}

//Shifts center of the body by specified offset
//Body should be stationary
void Body::shift(float dx, float dy){
    if (!this->locked){
        float right_x1 = legs[0].current_x;
        float left_x1 = legs[3].current_x;
        float front_z1 = legs[0].current_z;
        float back_z1 = legs[1].current_z;
        right_x1 -= dx;
        left_x1 += dx;
        front_z1 += dy;
        back_z1 += dy;
        set_position_leg(0, right_x1, -1000, front_z1);
        set_position_leg(1, right_x1, -1000, back_z1);
        set_position_leg(2, left_x1, -1000, back_z1);
        set_position_leg(3, left_x1, -1000, front_z1);
    }
}

//Converts to other leg frames
void Body::rotate_leg(float x1, float x2, int leg){
    //Will take the result of rotate and apply it to the given leg
    //Come up with formula pls
}

void Body::gait_next(){
    float result[3];
    int leg = this->gait.next(result);
    set_position_leg(leg, result[0], result[1], result[2]);
}

/* COMMUNICATION */

String Body::read_command(){
    String result = Serial.readStringUntil("\n");
    return result;
}

void Body::read_IMU(){
    Serial.println("IMU");
    int response = Serial.parseInt();
}

void Body::send_pose(){
    //int tilt_angle = calculate_tilt();
    print_val("Tilt: ", tilt_angle);
    float leg_pose[3];
    legs[0].get_position(leg_pose);
    print_val("Leg 1: ", leg_pose[0]);
    Serial.print(leg_pose[1]);
    Serial.println(leg_pose[2]);
    legs[1].get_position(leg_pose);
    print_val("Leg 2: ", leg_pose[0]);
    Serial.print(leg_pose[1]);
    Serial.println(leg_pose[2]);
    legs[2].get_position(leg_pose);
    print_val("Leg 3: ", leg_pose[0]);
    Serial.print(leg_pose[1]);
    Serial.println(leg_pose[2]);
    legs[3].get_position(leg_pose);
    print_val("Leg 4: ", leg_pose[0]);
    Serial.print(leg_pose[1]);
    Serial.println(leg_pose[2]);
}

/* LEG RELATED */

/* THIS SHOULD UPDATE THE PARAMETERS THAT THE BODY NEEDS TO KNOW
   FROM THE LEGS AND ALSO MAKE THE LEGS UPDATE THEMSELVES */

void Body::set_position_leg(int leg, float x, float y, float z){
    float answer[3];
    if (x == -1000) x = x_coords[leg];
    if (y == -1000) y = y_coords[leg];
    if (z == -1000) z = z_coords[leg];
    legs[leg].IK(x,y,z, false, answer, true);
}

void Body::set_angle_leg(int leg, int cox, int femur, int tibia){
    legs[leg].set_angles(cox, femur, tibia);
    legs[leg].update_angles();
}