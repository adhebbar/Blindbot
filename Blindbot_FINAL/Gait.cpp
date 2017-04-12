#include "Gait.h"
Gait::Gait(int num_gait_steps, int cycle, float leg_height, float walk_length){
  //this->timing = timing;
	this->cycle = num_gait_steps;
	GaitPos* legs = new GaitPos[4];
	walk_length = walk_length;
	leg_height = leg_height;
	leg = 1;
  	gait_step = 1;
}

int Gait::next(float coords[]){
	if (gait_step == 1){
		legs[leg].x = -1;
		legs[leg].y = leg_height/2;
		legs[leg].z = -1;
		gait_step++;
	}
	if(gait_step == 2){
		legs[leg].x = -1;
		legs[leg].y = leg_height;
		legs[leg].z = 0;
		gait_step++;
	}
	if(gait_step == 3){
		legs[leg].x = -1;
		legs[leg].y = leg_height/2;
		legs[leg].z = walk_length/2;
		gait_step++;
	}
	if (gait_step == 4){
		legs[leg].y = 0;
		gait_step++;
	}
	else
	{
		legs[leg].z -= walk_length/cycle;
		gait_step++;
	}

	if (gait_step > cycle){
		cycle_leg();
		gait_step = 0;
	}
}

void Gait::cycle_leg(){
	switch (leg){
		case 0: leg = 2; break; 
		case 1: leg = 0; break;
		case 2: leg = 3; break;
		case 3: leg = 1; break;
	}
}
