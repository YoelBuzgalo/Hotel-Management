#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

using namespace std;


class Customer
{
    public:
        Customer(string name, string password);
        void setCustomerName(string name);
        string getCustomerName();
        string getCustomerPassword();

    protected:

    private:
        string customerName;
        string customerPassword;
};

#endif // CUSTOMER_H
