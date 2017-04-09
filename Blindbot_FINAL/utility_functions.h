#include "Arduino.h"
#include "Robot.h"
#ifndef _UTILITY_H_
#define _UTILITY_H_
int convert_angle(float angle);
int convert_angle(float angle, float lower, float upper);
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max);
void print_val(String val_name, float val);
bool check_valid_pos(float x, float y, float z); //NEEDS TO BE IMPLEMENTED
int signed_area(float x[], float y[], int n);
void centroid_polygon(float* cx, float* cy,float x_coords[], float y_coords[], int legs);
void centroid_triangle(float* cx, float* cy, float x_coords[], float y_coords[], int legs);
float convert_to_kg(float forces[],int num_legs);
float convert_force(int force);
#endif