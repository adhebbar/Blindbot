#include "Body.h"
#include "Robot.h"
#include "A1_16.h"
#include "BOLIDE_Player.h"
#include "utility_functions.h"
#include "Leg.h"
#include "Arduino.h"

/* IMPLEMENTATION */

Body::Body(int* servos, HardwareSerial& serial, HardwareSerial& serial1, 
       HardwareSerial& serial2, HardwareSerial& serial3, bool joystick_connected = false):
legs({{int(servos[3*0]),int(servos[1+3*0]),int(servos[2+3*0]), 0, serial, A0, 0,true,true,true},
      {int(servos[3*1]),int(servos[1+3*1]),int(servos[2+3*1]), 1, serial1, A0, 0,true,false,false},
      {int(servos[3*2]),int(servos[1+3*2]),int(servos[2+3*2]), 2, serial2, A0, 0,false,true,true}, 
      {int(servos[3*3]),int(servos[1+3*3]),int(servos[2+3*3]), 3, serial3, A0, 0, false, false, false}})
{
  num_legs = 4;
  mode = GAIT;
  /*for (int i = 0; i < 4; i ++){
    switch(i){
      case 0: legs[i] = Leg();
      case 1: legs[i] = Leg(int(servos[3*i]),int(servos[1+3*i]),int(servos[2+3*i]), int(i), serial1, A0, 0);
      case 2: legs[i] = Leg(int(servos[3*i]),int(servos[1+3*i]),int(servos[2+3*i]), int(i), serial2, A0, 0);
      case 3: legs[i] = Leg(int(servos[3*i]),int(servos[1+3*i]),int(servos[2+3*i]), int(i), serial3, A0, 0);
    }
  }*/
  gait = Gait(20, 75.0, 145.0, 90.0);
  float coord_buff[3];
  for (int i = 0; i < num_legs; i++){
    legs[i].update_self(false);
    legs[i].get_position(coord_buff);
    x_coords[i] = coord_buff[0];
    y_coords[i] = coord_buff[1];
    z_coords[i] = coord_buff[2];
  }
  joystick = joystick_connected;
  //update_self();
}

void Body::update_self(){
  if(mode == GAIT && !joystick) gait_next();
  if(mode == BODY && !joystick) rotate_y(0.01);
  /*
  update_COM();
  update_acceleration();
  */
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
void Body::IK_pos(float &x2, float &z2, float &dist, float &angle, int leg){
  float x1 = x2; float z1 = z2;
  x2 = x1 + X_OFF;
  z2 = z1 + Y_OFF;
  dist = sqrt(x2*x2 + y2* y2);
  x2 = leg <= (num_legs-1)/2 ? x2 : -x2;
  z2 = leg % 
  angle = atan2(y2,x2);
}


void Body::rotate_y(int d_theta){
<<<<<<< HEAD
  float old_x, old_z, dist, angle;
  float new_x, new_z, IK_x, IK_y;
  for(int leg = 0; leg < num_legs; leg++){
    old_x = x_coords[leg];
    old_z = z_coords[leg];
    IK_pos(old_x, old_z, dist, angle, leg);
    new_x = dist*cos(d_theta+angle);
    new_y = dist*sin(d_teta+angle);
    IK_x = new_x - old_x;
    IK_z = new_z - old_z;
    set_position_leg(leg, x_coords[leg]+IK_x, y_coords[leg], z_coords[leg]+ IK_z);
  }
=======
    float x_answer[4];
    float z_answer[4];
    float x0 = x_coords[0];
    float z0 = x_coords[0];
    float R = sqrt(x0*x0 + z0*z0);
    float alpha = tan(z0/x0);
    float x_answer[0] = sqrt((R*R)/(1+tan(alpha+d_theta)*tan(alpha+d_theta)));
    float z_answer[0] = sqrt(R*R - x_answer[0]*x_answer[0]);
    for (int leg = 1; leg < 4; leg ++)
        rotate_leg(x_answer[0], z_answer[0], x_answer[leg], z_answer[leg], leg);
    for (int leg = 0; leg < 4; leg++)
      set_position_leg(leg, x_answer[leg], y_coords[leg], z_answer[leg]);
>>>>>>> 0964f500fbb6437b77848e643fd164730a79a57a
}

void Body::rotate_xz(float x_rotation, float z_rotation){
  float roll = tan();
}


//Shifts center of the body by specified offset
//Body should be stationary
void Body::shift(float dx, float dy){
    if (mode == BODY){
        float right_x1 = legs[0].current_x;
        float left_x1 = legs[3].current_x;
        float front_z1 = legs[0].current_z;
        float back_z1 = legs[1].current_z;
        right_x1 -= dx;
        left_x1 += dx;
        front_z1 += dy;
        back_z1 += dy;
        set_position_leg(0, right_x1, y_coords[0], front_z1);
        set_position_leg(1, right_x1, y_coords[1], back_z1);
        set_position_leg(2, left_x1, y_coords[2], back_z1);
        set_position_leg(3, left_x1, y_coords[3], front_z1);
    }
}

<<<<<<< HEAD
=======
//Converts to other leg frames
void Body::rotate_leg(float x1, float z1, float& x2, float& z2 int leg){
  if 9 
}

>>>>>>> 0964f500fbb6437b77848e643fd164730a79a57a
void Body::gait_next(){
    float result[12];
    gait.next(result);
    //Serial.println(result[0]);
    //Serial.println(result[1]);
    //Serial.println(result[2]);
    if(gait.gait_count > 1 && !gait.is_reversed())
      gait.reverse();
    set_position_leg(0, result[0], result[1], result[2], true);
    //delay(200);
    set_position_leg(1, result[3], result[4], result[5], true);
    //delay(200);
    set_position_leg(2, result[6], result[7], result[8], true);
    //delay(200);
    set_position_leg(3, result[9], result[10], result[11], true);
}

/* COMMUNICATION */

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
    Serial.print(leg_pose[1]);
    Serial.println(leg_pose[2]);
}

/* LEG RELATED */

/* THIS SHOULD UPDATE THE PARAMETERS THAT THE BODY NEEDS TO KNOW
   FROM THE LEGS AND ALSO MAKE THE LEGS UPDATE THEMSELVES */
    print_val("Leg 4: ", leg_pose[0]);

void Body::set_position_leg(int leg, float x, float y, float z, bool no_x = false){
    float answer[3];
    x_coords[leg] = no_x ? sqrt(x*x - z*z) : x;
    y_coords[leg] = y;
    z_coords[leg] = z;
    legs[leg].IK(x,y,z, answer, false, true, no_x);
}

void Body::set_angle_leg(int leg, int cox, int femur, int tibia){
    legs[leg].move_to_angles(cox,femur,tibia);
}

void Body::set_mode(int i){
    mode = i;
}

int Body::get_mode(){
    return mode;
}

void Body::joystick_command(char* command, int start){
    if (command[start] == "A")
        mode = GAIT;
    else if (command[start] == "B")
        mode = GAIT_AUTO;
    else if (command[start] == "X")
        mode = BODY;
    else if (command[start] == "Y")
        mode = LEGS;
    else if (command[start] = "LB")
        return;//unmapped
    else if (command[start] == "R")
        return;//unmapped
    else{
        return;
    }
}

void Body::joystick_movement(char* command){
    float dx, dy, dz;
    if(mode != GAIT){
        get_coords(command, dx, dy, dz);
    }
    if (mode == LEGS){
        float x_pos = x_coords[leg_current] + dx;
        float y_pos = y_coords[leg_current] + dy;
        float z_pos = z_coords[leg_current] + dz;
        set_position_leg(leg_current, x_pos, y_pos, z_pos);
    }
    else if (mode == BODY){
        shift(dx,dy);
    }
    else if (mode == GAIT){
        gait_next();
    }
}
