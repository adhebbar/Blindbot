#include "command_queue.h"

C_Queue::C_Queue(int capacity){
	command_q = new String [capacity];
	this->capacity = capacity;
	size = 0;
	front = 0;
	back = 0;
}



