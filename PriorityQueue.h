#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <class ItemType>
struct Node {
  ItemType info;
  int priority;
  Node<ItemType>* next;
};

class PQueueOverflow {
};

class PQueueUnderflow {
};

template <class ItemType>
class PriorityQueue {
 public:

  //constructor for default priority queue
  PriorityQueue();
  //constructor for priority queue with a set max size
  PriorityQueue(int max);
  //deletes all items in queue
  ~PriorityQueue();
  //resets queue to empty
  void makeEmpty();
  //if queue is empty returns true if it is not returns false
  bool isEmpty() const;
  //if queue is full returns true if it is not returns false
  bool isFull() const;
  //places newItem between lower and higher priorities or after items with equal priority
  void enqueue(ItemType newItem, int priority);
  //removes first item from queue
  void dequeuer();
  //returns length of queue
  int length();
  //returns all items stored within the queue in order of priority
  void printQueue(ofstream&);
  //returns the priority of the first item
  int peekPriority();
  //returns the information stored in the first item
  ItemType peek();

 private:
  Node<ItemType>* items;
  int size;
  int maxQue;
};

#endif
