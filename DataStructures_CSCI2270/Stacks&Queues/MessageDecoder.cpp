#include <iostream>
#include <cstdlib>
#include "MessageDecoder.hpp"

using namespace std;
# define SIZE 50

MessageDecoder::MessageDecoder()
{
	my_queue = new MyQueue();
	my_stack = new MyStack();
}

MessageDecoder::~MessageDecoder()
{
    delete my_queue;
    delete my_stack;	
}

/*
    generate_operator_queue(string jumbled_str)

    Takes the jumbled string as the input parameter and stores all the allowed operators in my_queue
*/
void MessageDecoder::generate_operator_queue(std::string jumbled_str){
    //TODO
    int length = jumbled_str.length();
    for(int i = 0; i < length; i++) {
        if(jumbled_str[i] == '+' || jumbled_str[i] == '-' || jumbled_str[i] == '*') {
            // enqueue character
            my_queue->enqueue(jumbled_str[i]);
        }
    }
}

/*
    generate_postfix(string jumbled_str)

    Takes the jumbled string as the input parameter and computes a postfix expression using the populated my_queue
    returns a postfix expression
*/
string MessageDecoder::generate_postfix(std::string jumbled_str) {
	string postfix = "";
    int count = 0;
    int iter = 0;
    for(int i = 0; i < jumbled_str.length(); i++) {
        if(isdigit(jumbled_str[i]) && count != 2) {
            postfix = postfix + jumbled_str[i];
            count++;
        } else if(count == 2 && !(my_queue->isEmpty())) {
            // append next operator in queue to postfix
            postfix = postfix + my_queue->peek();
            my_queue->dequeue();
            count = 0;
        }
        iter++;
    }

    if(!(my_queue->isEmpty())) {
        for(int i = 0; i < (my_queue->queueSize()+1); i++) {
            postfix = postfix + my_queue->peek();
            my_queue->dequeue();
        }
    }
    return postfix;
}

/* 
    evaluate_postfix(string postfix) 

    Takes the post fix string as an input parameter and evaluates the post fix string. 
    returns an integer after evaluating the postfix expression
*/

int MessageDecoder::evaluate_postfix(std::string postfix) {
    for(int i = 0; i < postfix.length(); i++) {
        if(isdigit(postfix[i])) {
            my_stack->push(postfix[i] - '0');
        } else if(postfix[i] == '+') {
            int num1 = (my_stack->peek())->val;
            my_stack->pop();
            int num2 = (my_stack->peek())->val;
            my_stack->pop();
            int num3 = num1 + num2;
            my_stack->push(num3);
            
        } else if(postfix[i] == '-') {
            int num1 = (my_stack->peek())->val;
            my_stack->pop();
            int num2 = (my_stack->peek())->val;
            my_stack->pop();
            int num3 = num2 - num1;
            my_stack->push(num3);
            
        } else if(postfix[i] == '*') {
            int num1 = (my_stack->peek())->val;
            my_stack->pop();
            int num2 = (my_stack->peek())->val;
            my_stack->pop();
            int num3 = num1 * num2;
            my_stack->push(num3);
        }
    }
    int result = (my_stack->peek())->val;
    my_stack->pop();
    return result;

}

// MyQueue* MessageDecoder::getQueue(){
//     return my_queue;
// }

// MyStack* MessageDecoder::getStack(){
//     return my_stack;
// }