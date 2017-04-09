#include "Robot.h"
#include "Leg.h"
#include "Gait.h"
#ifndef _BODY_H_
#define _BODY_H_
class Body{
    const int centroid_threshold;
    int num_legs;
    Leg legs[4];
    float x_coords[];
    float y_coords[];
    float z_coords[];
    int x_offset, y_offset; //distance from center of body to legs
    int speed_setting;
    int height; //distance from the ground
    int tilt_angle;
    float cx, cy, cz; //center of mass
    float abs_x, abs_y, abs_z; //absolute position
    float ax, ay, az;
    Gait gait;
    bool locked;
    public:
        Body(int servos[], HardwareSerial& serial, HardwareSerial& serial1, 
             HardwareSerial& serial2, HardwareSerial& serial3);
        void set_position_leg(int leg, float x, float y, float z);
        void set_angle_leg(int leg, int cox_angle, int femur_angle, int tibia_angle);
        int read_force_leg(int leg);
        void set_gait(Gait gait);
        void gait_next();    
        String read_command();
        void send_message(String message);
        void send_pose();
        void balance();
        void balance_triangle();
        void update_COM();
        void IK(float x, float y, float z);
        void calculate_tilt();
        void set_speed(int speed);
        void rotate();
        void set_height(int h);
        void update_acceleration();
        void update_self(); //makes all legs refresh themselves
        void read_IMU();
        void rotate_y(int d_theta);
        void shift(float dx, float dy);
        void rotate_leg(float x1, float x2, int leg);
};
#endif
