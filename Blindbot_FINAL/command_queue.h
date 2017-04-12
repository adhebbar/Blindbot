#ifndef _COMMAND_QUEUE_H_
#define _COMMAND_QUEUE_H_
#include "Arduino.h"
class C_Queue{
	int q_size;
	int capacity;
	int front;
	int back;
	char** command_q;
	public:
		C_Queue(int capacity);
		char* deq();
		void enq(char* elem);
		int queue_size();
		int queue_capacity();
		char* queue_peek(int index);
};
#endif
