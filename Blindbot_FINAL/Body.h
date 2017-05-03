#include "Robot.h"
#include "Leg.h"
#include "Gait.h"
#ifndef _BODY_H_
#define _BODY_H_

enum Modes { LEGS = 1, GAIT = 2, BODY = 3, LOCK = 4, GAIT_AUTO = 5};
class Body{
    const int centroid_threshold;
    int num_legs;
    Leg legs[4];
    float x_coords[4];
    float y_coords[4];
    float z_coords[4];
    int forces[4];
    int x_offset, y_offset; //distance from center of body to legs
    int speed_setting;
    int height; //distance from the ground
    int tilt_angle;
    float cx, cy, cz; //center of mass
    float abs_x, abs_y, abs_z; //absolute position
    float ax, ay, az;
    Gait gait;
    Modes mode;
    int leg_current;
    bool joystick;
    public:
        Body(int servos[], HardwareSerial& serial, HardwareSerial& serial1, 
             HardwareSerial& serial2, HardwareSerial& serial3, bool joystick_connected = false);
        //POSE UPDATE
        void gait_next();
        void update_acceleration();
        void update_self();    
        void balance();
        void update_COM();
        void balance_triangle();
        // BODY INVERSE KINEMATICS
        void IK_pos(float &x2, float &z2, float &dist, float &angle, int leg);
        void rotate_xz(float x_rotation, float z_rotation);
        void rotate_y(int d_theta);
        void shift(float dx, float dy);
        //LEG CONTROL
        void set_position_leg(int leg, float x, float y, float z, bool no_x = false);
        void set_angle_leg(int leg, int cox_angle, int femur_angle, int tibia_angle);
        //SENSOR READING
        void read_IMU();
        void calculate_tilt();
        int read_force_leg(int leg);
        //COMMS
        void send_message(char* message);
        void send_pose();
        //makes all legs refresh themselves
        int get_mode();
        //SETTERS
        void set_mode(int i);
        void set_height(int h);
        void set_gait(Gait gait);
        void set_speed(int speed);
        
        //WORK IN PROGRESS JOYSTICK COMMANDS
        void joystick_command(char* command, int start);
        void joystick_movement(char* command);
};
#endif
