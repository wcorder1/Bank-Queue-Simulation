#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>

class Customer
{

 private:
  std::string name;
  int arrival = 0;
  int service = 0;
  int wait = 0;
  int departure = 0;

 public:
  Customer();
  void setName(std::string newName);
  void setArrival(int newArriv);
  void setService(int newServ);
  void setWait(int newWait);
  std::string getName() const;
  int getArrival() const;
  int getService() const;
  int getWait() const;
  int getDeparture() const;
  
  friend std::ostream& operator << (std::ostream &out, const Customer &cust);

};

#endif
