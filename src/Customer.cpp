#include "Customer.h"
#include <string>
#include <iostream>

using namespace std;

Customer::Customer(string name, string password)
:customerName(name), customerPassword(password)
{
}

void Customer::setCustomerName(string name){
    this->customerName = name;
}

string Customer::getCustomerName(){
    return this->customerName;
}

string Customer::getCustomerPassword(){
    return this->customerPassword;
}
