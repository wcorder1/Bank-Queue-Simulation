#include "Customer.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

Customer::Customer() {
  name = "Todd";
  arrival = rand() % 25200;
  service = rand() % 361 + 120;
}

void Customer::setName(std::string newName) {
  name = newName;
}

void Customer::setArrival(int newArriv) {
  arrival = newArriv;
}

void Customer::setService(int newServ) {
  service = newServ;
}

void Customer::setWait(int newWait) {
  wait = newWait;
}

std::string Customer::getName() const {
  return name;
}

int Customer::getArrival() const {
  return arrival;
}

int Customer::getService() const {
  return service;
}

int Customer::getWait() const {
  return wait;
}

int Customer::getDeparture() const {  
  return (this->getWait() + this->getService() + this->getArrival());
}

/*Overriding the ostream operator for Customer so it prints all
  of the private variables all at once*/
std::ostream & operator << (std::ostream &out, const Customer &cust) {
  out << "  " << cust.getName() <<  " " << cust.getWait() << " wait  service " << cust.getDeparture();
}

