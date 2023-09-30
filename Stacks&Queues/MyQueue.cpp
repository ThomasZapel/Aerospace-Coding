#include "MyQueue.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

MyQueue::MyQueue() {
    queueFront = -1;
	queueEnd = -1;
}

bool MyQueue::isEmpty() {
	if(counter == 0) {
		return true;
	} else {
		return false;
	}
}

bool MyQueue::isFull(){
	if(counter == SIZE) {
		return true;
	} else {
		return false;
	}
}

void MyQueue::enqueue(char ch) {
	if(!MyQueue::isFull()) {
		// add to queue
		if(queueFront == -1) {
			// first element
			queueFront = 0;
			queueEnd = 0;
			queue[counter] = ch;
			counter++;
		} else if(queueEnd == SIZE-1 && queueFront != 0) {
			// adding element when front is not pointing to 0th index
			queueEnd = 0;
			queue[0] = ch;
			counter++;
		} else {
			queueEnd++;
			queue[queueEnd] = ch;
			counter++;
		}
	} else {
		cout << "Queue full, cannot add!\n";
	}
}


void MyQueue::dequeue() {
	if(!MyQueue::isEmpty()) {
		// remove from queue
		if(counter == 1) {
			// one element remaining
			queueFront = -1;
			queueEnd = -1;
			counter = 0;
		} else if(queueFront == SIZE-1) {
			// wrap front around to start of queue
			queueFront = 0;
			counter--;
		} else {
			// general case
			queueFront++;
			counter--;
		}
	} else {
		cout << "Queue empty, cannot dequeue!\n";
	}
}


char MyQueue::peek() {
	if(MyQueue::isEmpty()) {
		cout << "Queue empty, cannot peek!\n";
		return '\0';
	} else {
		return queue[queueFront];
	}
}

int MyQueue::queueSize() {
    return counter;
}
