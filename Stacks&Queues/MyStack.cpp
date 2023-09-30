#include <iostream>
#include <cstdlib>
#include <iostream>
#include "MyStack.hpp"

using namespace std;

MyStack::MyStack() {
	head = NULL;
}

MyStack::~MyStack() {
	Node *pres = head;
    while(pres != 0) {
      Node *prev = pres;
      pres = pres->next;
      delete prev;
    }
}

bool MyStack::isEmpty() {
	if(head == 0) {
		return true;
	} else {
		return false;
	}
}

void MyStack::push(int val) {
	Node *newVal = new Node;
	newVal->val = val;
	Node *temp = head;
	head = newVal;
	newVal->next = temp;
}

void MyStack::pop() {   
	if(!MyStack::isEmpty()) {
		// pop top of stack
		Node *temp = head;
      	head = head->next;
      	delete temp;
	} else {
		// stack empty
		cout << "Stack empty, cannot pop an item!\n";
	}
}

Node* MyStack::peek() {
	if(!MyStack::isEmpty()) {
		// return top of stack
		return head;
	} else {
		// stack empty
		cout << "Stack empty, cannot peek!\n";
		return nullptr;
	}
}
