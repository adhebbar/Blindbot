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


void centroid_polygon(float &cx, float &cy, float x_coords[], float y_coords[], int legs){
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

void centroid_triangle(float& cx, float& cy, float x_coords[], float y_coords[], int legs){
    float x_sum = 0;
    float y_sum = 0;
    for (int i = 0; i < legs; i++){
        x_sum += x_coords[i];
        y_sum += y_coords[i];
    }
    cx = x_sum/3;
    cy = y_sum/3;
}

void get_command(char command[]){
  char instruction = command[0];
  char buffer[10];
  switch (instruction){
    case 'S': {
      for (int i = 0; command[i] != '\n'; i++)
        buffer[1+i] = command[i];
      
      break;
    }
    case 'M': break;
    case 'R': break;
    case 'T': break;
    case 'B': break;
  }

}

void get_coords(char command[], float& dx, float& dy, int& dz){
    char* buffer = new char[PRECISION]();
    int i = 0;
    int count = 1;
    int start;
    while(i < PRECISION){
        if (!isDigit(command[i])){
            while (!isDigit(command[i]))
                i++;
            start = i;
        }
        if (command[i] == ' '){
            switch (count){
                case 1: dx = (float)atof(buffer); 
                              count++;
                              break;
                case 2: dy = (float)atof(buffer); 
                             count++;
                             break;
                case 3: dz = (float)atof(buffer); break;
            }
            if (count == 3){
                delete(buffer);
                return;
            }
            start = i;
        }
        buffer[i-start] = command[i];
        i++;
    }
    delete buffer;
}


bool constraints(float x, float y, float z)
{  
  float leg_length= x*x+ z*z;
    if ( (leg_length)>(COX_LEN + FEMUR_LEN + TIBIA_LEN)*(COX_LEN + FEMUR_LEN + TIBIA_LEN) ) return false;
    float temp_hf = (leg_length - COX_LEN)*(leg_length-COX_LEN) + y*y;
    if (temp_hf<0) return false;
    float HF=  sqrt((temp_hf*temp_hf + y*y)) ;
    if (abs((TIBIA_LEN*TIBIA_LEN- FEMUR_LEN*FEMUR_LEN- HF*HF)/(2*FEMUR_LEN*HF))>1) return false;    
    if (abs((TIBIA_LEN*TIBIA_LEN +FEMUR_LEN*FEMUR_LEN- HF*HF)/(2*FEMUR_LEN*HF))>1) return false;
    return true;
}

//TODO revise this
bool check_within_triangle(point p1, point p2, point p3, point p){
    //not sure about arguments , this ish is in terms of structures p1,p2,p3
    // point p1(x1, y1);
    // point p2(x2, y2);
    // point p3(x3, y3);
    // point p(x,y);
    float alpha = ((p2.y - p3.y)*(p.x - p3.x) + (p3.x - p2.x)*(p.y - p3.y)) /
            ((p2.y - p3.y)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.y - p3.y));
    float beta = ((p3.y - p1.y)*(p.x - p3.x) + (p1.x - p3.x)*(p.y - p3.y)) /
           ((p2.y - p3.y)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.y - p3.y));
    float gamma = 1.0f - alpha - beta;
     
    if (alpha<=0  || beta<=0 || gamma<=0) return false;
    return true;
}

bool check_within_quadrilateral(float x_coords[], float y_coords[])
{
  point p1 = {x_coords[0], y_coords[0]};
  point p2 = {x_coords[1], y_coords[1]};
  point p3 = {x_coords[2], y_coords[2]};
  point p4 = {x_coords[3], y_coords[3]};

  return (check_within_triangle(p1,p2,p3,p1) && 
        check_within_triangle(p2,p3,p4,p1));
}
