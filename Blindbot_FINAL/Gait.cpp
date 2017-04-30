#include "Gait.h"
#include "Arduino.h"
Gait::Gait(int num_gait_steps, float L, float leg_height, float walk_length){
  //this->timing = timing;
	cycle = num_gait_steps;
	walk_length = walk_length;
	leg_height = leg_height;
	leg = 0;
  gait_step = 1;
  first_gait = false;
  for (int leg_index = 0; leg_index < 4; leg_index++){
  	legs[leg_index].x = L;
  	legs[leg_index].y = leg_height;
  	legs[leg_index].z = 0;
  }
}

int Gait::next(float coords[]){
  for (int leg_index = 0; leg_index < 4; leg_index++){
  	if (gait_step == 1 && leg_index == leg){
  		legs[leg].y = leg_height*0.75;
  		gait_step++;
  	}
  	else if(gait_step == 2 && leg_index == leg){
  		legs[leg].y = leg_height/2.0;
  		legs[leg].z = 0;
  		gait_step++;
  	}
  	else if(gait_step == 3 && leg_index == leg){
  		legs[leg].y = leg_height*0.75;
  		legs[leg].z = walk_length/2.0;
  		gait_step++;
  	}
  	else if (gait_step == 4 && leg_index == leg){
      legs[leg].z = walk_length;
  		legs[leg].y = leg_height;
  		gait_step++;
  	}
  	else if(leg_index != leg && (first_gait||(leg_index < leg&& leg_index != 0)))
  	{
      legs[leg_index].z -= walk_length/cycle*2.0;
  		gait_step++;
  	}
  	if (gait_step > cycle/4){
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
	switch (leg){
		case 0: leg = 2; break; 
		case 1: leg = 0; break;
		case 2: leg = 3; break;
		case 3: leg = 1; first_gait = true; break;
	}
}
