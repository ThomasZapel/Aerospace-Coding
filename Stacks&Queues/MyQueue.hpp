#ifndef MyQueue_H__
#define MyQueue_H__

#pragma once

#include <string>

const int SIZE = 20;

class MyQueue
{
private:
  int queueFront; //the index in queue[] that will be dequeued next
  int queueEnd; //the index in queue[] that was most recently enqueued
  int counter = 0; //to keep track the number of characters in the queue
  char queue[SIZE];

public:
  MyQueue();
  bool isEmpty();
  bool isFull();
  void enqueue(char ch);
  void dequeue();
  char peek();
  int queueSize();   
  int getQueueFront() { return queueFront; }
  int getQueueEnd() { return queueEnd; }
  char* getQueue() { return queue; }
};
#endif
