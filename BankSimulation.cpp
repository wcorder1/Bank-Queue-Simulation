#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <string>
#include "Customer.cpp"
#include "PriorityQueue.cpp"
#include "QueType.cpp"

using namespace std;

//reads the inFile to determine number of customers and tellers
QueType<Customer> readIn(ifstream&, int&, int&);

//places elements equal to the number of tellers into the priority queue from the original queue
void initialize(QueType<Customer>&, PriorityQueue<Customer>&, int);

//checks if a teller can be freed if their departure time is equal to the current time
void freeTeller(QueType<Customer>&, PriorityQueue<Customer>&, PriorityQueue<Customer>&, ofstream&, float&, int, int&);

/*checks if the head of the customers queue's arrival time is equal to the current time to see
  it can be queued then determines if it needs to be added to the waiting queue or the servicing queue*/
void newCustomer(QueType<Customer>&, QueType<Customer>&, PriorityQueue<Customer>&, ofstream&, int);

//prints the list of customers who are waiting and customers who are being serviced
void printCust(QueType<Customer>&, PriorityQueue<Customer>&, ofstream&, int, int);



int main() {

  ofstream outFile;
  ifstream inFile;
  float averageWait = 0;
  int numCust = 0;
  int numTell = 0;
  int count = 0;

  inFile.open("inFile.txt");
  
  QueType<Customer> customers = readIn(inFile, numCust, numTell); //queue for unserviced customers
  QueType<Customer> waiting(numCust); //queue for customers waiting in line
  PriorityQueue<Customer> servicing(numTell); //queue for customers being serviced
  PriorityQueue<Customer> serviced(numCust); //queue that holds customers who have been processed

  outFile.open("outFile.txt");
  int seconds = customers.peek().getArrival();

  while (seconds <= 25200 || servicing.length() != 0) {
    newCustomer(customers, waiting, servicing, outFile, seconds);
    freeTeller(waiting, servicing, serviced, outFile, averageWait, seconds, count);

    //a series of if statements to set the current time to either the nearest departure time or arrival time
    if (customers.isEmpty() && servicing.isEmpty()) {
      break;
    }else if (customers.isEmpty()) {
      seconds = servicing.peekPriority();
    } else if (servicing.isEmpty() == false && (servicing.peekPriority() <= customers.peek().getArrival())) {
      seconds = servicing.peekPriority();
    } else {
      seconds = customers.peek().getArrival();
    }
  }

  serviced.printQueue(outFile);
  outFile << endl << "Average wait time = " << averageWait/numCust << " seconds." << endl;

  outFile.close();
  servicing.~PriorityQueue();
  serviced.~PriorityQueue();

  return 0;
}



void freeTeller(QueType<Customer>& waiting, PriorityQueue<Customer>& servicing, PriorityQueue<Customer>& serviced, ofstream& outFile, float& averageWait, int seconds, int& count) {
  
  if ((servicing.length() != 0) && (servicing.peekPriority() == seconds)) {

    serviced.enqueue(servicing.peek(), servicing.peekPriority());
    servicing.dequeuer();
    count++;

    if (count % 5 == 0) {
      printCust(waiting, servicing, outFile, count, seconds);
    }

    /*if there is something within the waiting queue then it will be placed
      into the servicing queue once servicing has dequeued*/
    if (waiting.isEmpty() == false) {
      Customer temp = waiting.peek();
      int newWait = (seconds - temp.getArrival());
      averageWait += newWait;
      temp.setWait(newWait);
      servicing.enqueue(temp, temp.getDeparture());
      waiting.dequeue();
    }
  }
}



void newCustomer(QueType<Customer>& customers, QueType<Customer>& waiting, PriorityQueue<Customer>& servicing, ofstream& outFile, int seconds) {
  
  while ((customers.length() != 0) && (customers.peek().getArrival() == seconds)) {
    /*case for if tellers are available,
      places new customer into servicing queue*/
    if (waiting.isEmpty() && (servicing.isFull() == false)) {      
      servicing.enqueue(customers.peek(), customers.peek().getDeparture());
    }   
    /*case for if no tellers are available,
      places customer into waiting queue*/
    else {
      waiting.enqueue(customers.peek());
    }

    customers.dequeue();
  }
}



void initialize(QueType<Customer>& customers, PriorityQueue<Customer>& servicing,  int numTell) {
  
  for (int i = 0; i < numTell; i++) {
    servicing.enqueue(customers.peek(), customers.peek().getDeparture());
    customers.dequeue();
    
    if (customers.isEmpty()) {
      break;
    }
  }
}



void printCust(QueType<Customer>& waiting, PriorityQueue<Customer>& servicing, ofstream& outFile, int count, int seconds) {
  
  for (int i = 0; i < waiting.length(); i++) {
    waiting.reference(i).setWait(seconds - waiting.reference(i).getArrival());
  }
  
  outFile << "Customer " << count << " Left at Time : " << seconds << endl;
  outFile << "Customers currently being serviced:" << endl;
  servicing.printQueue(outFile);
  outFile << "Customers currently waiting:" << endl;
  waiting.printQueue(outFile);
  outFile << endl;
}



QueType<Customer> readIn(ifstream& inFile, int& numCust, int& numTell) {

  string command;
  int Arrival;
  int Service;
 
  for (int numCom = 0; numCom < 2; numCom++) {
    inFile >> command;
    if (command == "numTellers") {
      inFile >> numTell;
    }
    else if (command == "numCustomers") {
      inFile >> numCust;
    }
    else {
      cout << "Invalid Command";
      exit;
    }
  }

  QueType<Customer> customers(numCust);
  Customer init[numCust];

  for (int i = 0; i < (numCust*3); i++) {
    inFile >> command;
    
    if (i%3 == 0) {
      init[i/3].setName(command);
    }
    else if (command == "arrival") {
      inFile >> Arrival;
      init[i/3].setArrival(Arrival);
    }
    else if (command == "service") {
      inFile >> Service;
      init[i/3].setService(Service);
    }
    else {
      cout << "Invalid Command";
      exit;
    }
  }

  for (int i = 0; i < numCust; i++) {
    customers.enqueue(init[i]);
  }
  return customers;
}  
