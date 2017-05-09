#include "Gait.h"
#include "Arduino.h"
#include "Robot.h"
Gait::Gait(int num_gait_steps, float L, float leg_height, float walk_length){
	cycle = num_gait_steps;
  this->L = L;
	this->walk_length = walk_length;
	this->leg_height = leg_height;
	leg = 1;
  gait_step = 1;
  reversed = 1;
  gait_count = 0;
  restart();
}

int Gait::next(float coords[]){
  for (int leg_index = 0; leg_index < 4; leg_index++){
  	if (gait_step == 1 && leg_index == leg){
  		legs[leg].x = L - 15.0;
  		legs[leg].y = leg_height*0.75;
      	//legs[(leg+2)%4].y -= 10.0;
  		gait_step++;
  	}
  	else if(gait_step == 2 && leg_index == leg){
  		legs[leg].y = leg_height*0.5;
     	//legs[(leg+2)%4].y -= 30.0;
  		if(leg % 3 == 0) legs[leg].z = is_reversed() ? 10+walk_length/2.0 : 10;
      else legs[leg].z = !is_reversed() ? -Z_ZERO : 0;
  		gait_step++;
  	}
  	else if(gait_step == 3 && leg_index == leg){
  		legs[leg].y = leg_height*0.75;
  		legs[leg].z = legs[leg].z + walk_length*0.5*reversed;
  		gait_step++;
  	}
  	else if (gait_step == 4 && leg_index == leg){
      	//legs[(leg+2)%4].y = leg_height;
  		legs[leg].y = leg_height;
  		gait_step++;
  	}
  	else if(leg_index != leg && (first_gait[leg_index])){
      legs[leg_index].z = legs[leg_index].z - walk_length/cycle*reversed;
  	}
  	if (gait_step >= cycle/4){
  		cycle_leg();
  		gait_step = 1;

  	}
  }
  coords[0] = legs[0].x;
  coords[1] = legs[0].y;
  coords[2] = legs[0].z;
  coords[3] = legs[1].x;
  coords[4] = legs[1].y;
  coords[5] = legs[1].z;
  coords[6] = legs[2].x;
  coords[7] = legs[2].y;
  coords[8] = legs[2].z;
  coords[9] = legs[3].x;
  coords[10] = legs[3].y;
  coords[11] = legs[3].z;
}

void Gait::cycle_leg(){
  first_gait[leg] = true;
	if(reversed == 1){
  	switch (leg){
  		case 0: leg = 2; break; 
  		case 1: leg = 0; break;
  		case 2: leg = 3; break;
  		case 3: leg = 1; gait_count++; break;
  	}
	}
  else{
      switch(leg){
      case 0: leg = 1; break;
      case 1: leg = 3; gait_count ++; break;
      case 2: leg = 0; break;
      case 3: leg = 2; break;
    }
  }
}

void Gait::reverse(){
  restart();
  reversed *= -1;
}

void Gait::restart(){
  if(is_reversed()) leg = 3;
  else leg = 1;
  for (int leg_index = 0; leg_index < 4; leg_index++){
    first_gait[leg_index] = false;
    legs[leg_index].x = L;
    legs[leg_index].y = leg_height;
    if(leg_index == 0 || leg_index == 3) legs[leg_index].z = Z_ZERO;
    else legs[leg_index].z = -Z_ZERO;
  }
}

bool Gait::is_reversed(){
  return reversed == -1;
}

