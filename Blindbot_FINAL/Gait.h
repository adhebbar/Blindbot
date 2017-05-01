#ifndef _GAIT_H_
#define _GAIT_H_
typedef struct GaitPos GaitPos;
struct GaitPos{
  float x;
  float y;
  float z;
};

class Gait{
  int reversed;
	int gait_step;
	int leg;
	int cycle;
	float leg_height;
	float walk_length;
	bool first_gait[4] = {false, false, false, false};
  float L;
	GaitPos legs[4];
	public:
    int gait_count;
		void restart();
		void reverse();
    int next(float coords[]);
    void cycle_leg();
    bool is_reversed();
    Gait(){}
		Gait(int num_steps, float L, float leg_height, float walk_length);
};
#endif
