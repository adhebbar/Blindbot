#ifndef _COMMAND_QUEUE_H_
#define _COMMAND_QUEUE_H_
#include "Arduino.h"
class C_Queue{
	int q_size;
	int capacity;
	int front;
	int back;
	String* command_q;
	public:
		C_Queue(int capacity);
		String deq();
		void enq(String elem);
		int queue_size();
		int queue_capacity();
		String queue_peek(int index);
};
#endif
