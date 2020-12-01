#include <iostream>
#include "PriorityQueue.h"

using namespace std;

template <class ItemType>
PriorityQueue <ItemType>::PriorityQueue() {
  items = NULL;
  maxQue = 150;
  size = 0;
}


template <class ItemType>
PriorityQueue <ItemType>::PriorityQueue(int max) {
  items = NULL;
  maxQue = max;
  size = 0;
}


template <class ItemType>
PriorityQueue <ItemType>::~PriorityQueue() {

  Node<ItemType>* location;

  while (items != NULL) {
    location = items;
    items = location->next;
    delete location;
  }  
}


template <class ItemType>
void PriorityQueue <ItemType>::makeEmpty() {

  Node<ItemType>* location;

  while (items != NULL) {
    location = items;
    items = location->next;
    delete location;
  }

  items = new Node<ItemType>;
  items = NULL;
  size = 0;
}


template <class ItemType>
bool PriorityQueue <ItemType>::isEmpty() const {
  return bool (items == NULL);
}


template <class ItemType>
bool PriorityQueue <ItemType>::isFull() const {
  return bool (size == maxQue);
}


template <class ItemType>
void PriorityQueue <ItemType>::enqueue(ItemType newItem, int priority) {
  if (isFull()) { throw PQueueOverflow(); }

  Node<ItemType>* location = items;
  Node<ItemType>* temp;
  Node<ItemType>* newNode;

  newNode = new Node<ItemType>;
  newNode->info = newItem;
  newNode->priority = priority;
  newNode->next = NULL;

  if (isEmpty()) {
    items = newNode;
    size++;
  }

  else if (priority < items->priority) {
    temp = items;
    items = newNode;
    items->next = temp;
    size++;
  }

  else {
    while (location->next != NULL && priority >= location->next->priority) {
      location = location->next;
    }
    temp = location->next;
    location->next = newNode;
    location->next = newNode;
    location->next->next = temp;
    size++;
  }
}


template <class ItemType>
void PriorityQueue <ItemType>::dequeuer() {
  Node<ItemType>* temp;

  if (isEmpty()) { throw PQueueUnderflow(); }

  else if (size == 1) {
    delete items;
    items = NULL;
    size--;
  }

  else {
    temp = items->next;
    delete items;
    items = temp;
    size--;
  }
}


template <class ItemType>
int PriorityQueue <ItemType>::length() {
  return size;
}


template <class ItemType>
void PriorityQueue <ItemType>::printQueue(ofstream& outFile) {

  Node<ItemType>* location = items;

  while (location != NULL) {
    outFile << location->info;
    outFile << endl;
    location = location->next;
  }
}



template <class ItemType>
ItemType PriorityQueue <ItemType>::peek() {
  if (isEmpty()) { throw PQueueUnderflow(); }

  else {
    return items->info;
  }
}


template <class ItemType>
int PriorityQueue <ItemType>::peekPriority() {
  if (isEmpty()) { throw PQueueUnderflow(); }

  else {
    return items->priority;
  }
}
