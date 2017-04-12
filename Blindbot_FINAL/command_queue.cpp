#include "command_queue.h"

C_Queue::C_Queue(int capacity){
	command_q = new String [capacity];
	this->capacity = capacity;
	size = 0;
	front = 0;
	back = 0;
}

int queue_size(){
	return size;
}

int queue_capacity(){
	return capacity;
}

void enq(String elem){
	if (size == capacity) return;
	if (size == 0){
		front = 0;
		back = 1;
		command_q[front] = elem;
	}
	command_q[back&capacity] = elem;
	back = (back + 1)%capacity;
}

String deq(){
	if (size == 0) return;
	String elem = command_q[front];
	front = (front + 1) % capacity;
	return elem;
}

String queeu_peek(int index){
	if (index > size) return;
	return command_q[(front+i)% capacity];
}