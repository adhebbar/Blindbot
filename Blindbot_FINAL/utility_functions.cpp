//put this in a header file
#include "utility_functions.h"
#include "SoftwareSerial.h"
int convert_angle(float angle){
  return mapfloat(angle, -pi/2, pi/2, 256.0, 768.0);
}

int convert_angle(float angle, float lower, float upper){
  return mapfloat(angle, lower, upper, 0.0, 1024.0);
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void print_val(String val_name, float val)
{
   Serial.print(val_name);
   Serial.println(val);
}

void print_val(String val_name, float val, SoftwareSerial& serial){
  serial.print(val_name);
  serial.println(val);
}


int signed_area(float x[], float y[], int n){
    float area = 0;
    for (int i = 0; i< n; i++){
        area += x[i]*y[(i+1)%n] - x[(i+1)%n]*y[i];
    }
    return area/2;
}


void centroid_polygon(float* cx, float* cy, float x_coords[], float y_coords[], int legs){
    float area = signed_area(x_coords, y_coords, legs);
    float centroid_x = 0;
    float centroid_y = 0;
    for (int i = 0; i < legs; i++){
        centroid_x = (x_coords[i]*x_coords[(i+1)%legs])*
                     (x_coords[i]*y_coords[(i+1)%legs]-
                      x_coords[(i+1)%legs]*y_coords[i]);
        centroid_y = (y_coords[i]*y_coords[(i+1)%legs])*
                     (x_coords[i]*y_coords[(i+1)%legs]-
                      x_coords[(i+1)%legs]*y_coords[i]);
    }
    *cx = centroid_x/(6*area);
    *cy = centroid_y/(6*area);
}

void centroid_triangle(float* cx, float* cy, float x_coords[], float y_coords[], int legs){
    float x_sum = 0;
    float y_sum = 0;
    for (int i = 0; i < legs; i++){
        x_sum += x_coords[i];
        y_sum += y_coords[i];
    }
    *cx = x_sum/3;
    *cy = y_sum/3;
}


