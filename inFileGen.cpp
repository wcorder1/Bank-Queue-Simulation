#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include "Customer.cpp"

using namespace std;

int main() {

  srand(time(NULL));
  ofstream outFile;
  ifstream inFile;
  int numTell = 2;
  int numCust = 150;

  outFile.open("inFile.txt");

  outFile << "numTellers " << numTell << endl;
  outFile << "numCustomers " << numCust << endl;

  Customer init[numCust];
  Customer temp;

  for (int i = 0; i < numCust-1; i++) {
    for (int j = 0; j < numCust - i - 1; j++) {
      if (init[j].getArrival() > init[j+1].getArrival()) {
	temp = init[j];
	init[j] = init[j+1];
	init[j+1] = temp;
      }
    }
  }

  for (int k = 0; k < numCust; k++) {
    outFile << "Customer" + to_string(k+1) << " arrival " << init[k].getArrival() << " service " << init[k].getService() << endl;
  }

  outFile.close();
  
}
