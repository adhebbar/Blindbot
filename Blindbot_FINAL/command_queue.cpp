#include "command_queue.h"
C_Queue::C_Queue(int capacity){
	command_q = new String [capacity];
	this->capacity = capacity;
	q_size = 0;
	front = 0;
	back = 0;
}

int C_Queue::queue_size(){
	return q_size;
}

int C_Queue::queue_capacity(){
	return capacity;
}

void C_Queue::enq(String elem){
	if (q_size == capacity) return;
	if (q_size == 0){
		front = 0;
		back = 1;
		command_q[front] = elem;
	}
	command_q[back&capacity] = elem;
	back = (back + 1)%capacity;
}

String C_Queue::deq(){
	if (q_size == 0) return;
	String elem = command_q[front];
	front = (front + 1) % capacity;
	return elem;
}

String C_Queue::queue_peek(int index){
	if (index > q_size) return;
	return command_q[(front+index)% capacity];
}
