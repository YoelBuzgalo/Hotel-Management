#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include "Customer.h"
#include "Room.h"

using namespace std;

class Booking
{
    public:
        Booking(Customer* newCustomerIndex, int newBookingIndex, string newCheckInDate, string newCheckOutDate, int amount, Room* selectedRoom);
        void setAmountOfPeople(int amount);
        int getAmountOfPeople();
        Customer* getCustomerID();
        int getBookingID();
        int getCost();
        long long getCheckInDate();
        long long getCheckOutDate();
        long long convertToTimestamp(string date);
        string convertToDate(long long timestamp);
        string bookingDescription();


    protected:

    private:
        Customer* customerID;
        int bookingID;
        int cost;
        int amountOfPeople;
        long long checkInDate;
        long long checkOutDate;
        Room* room;
};

#endif // BOOKING_H
