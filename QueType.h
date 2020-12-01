#ifndef QUETYPE_H
#define QUETYPE_H
#include <iostream>

using namespace std;

#include <fstream>
#include <string>

class QueueOverflow {
};

class QueueUnderflow {
};

template <class ItemType>
class QueType
{

 public:

  //declares a default queue
  QueType();
  //declares a queue with a defined max
  QueType(int max);
  //deconstructor to delete whole queue
  ~QueType();
  //will essentially run deconstructor then constructor, end result is an empty queue
  void makeEmpty();
  //true if queue is empty false if it is not
  bool isEmpty() const;
  //true if queue is full false if it is not
  bool isFull() const;
  //places newItem at end of queue
  void enqueue(ItemType newItem);
  //removes first item from the queue
  void dequeue ();
  
  /*new added function, returns the value in the queue
    at the referenced integer*/
  ItemType& reference(int);
  
  //returns value stored in first item
  ItemType peek();
  //returns length of queue
  int length();
  //prints all items within the queue
  void printQueue(ofstream&);
  
 private:
  
  int front;
  int rear;
  ItemType* items;
  int maxQue;

};

#endif
