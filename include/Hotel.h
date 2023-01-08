#ifndef HOTEL_H
#define HOTEL_H

#include "Customer.h"
#include "Room.h"
#include "Booking.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Hotel
{
    public:
        Hotel();
        void start();
        void handleLogin();
        void handleCreateAccount();
        void handleLogout();
        void createReservationBooking();
        void deleteReservationBooking();
        Customer* findUser(string name);
        long long convertToTimestamp(string date);
        string convertToDate(long long timestamp);
        void viewReservationBooking();

    protected:

    private:
        Customer* CurrentLoggedInCustomer;
        vector <Customer*> CustomerList;
        vector <Booking*> BookingList;
        vector <Room*> RoomList;
};

#endif // HOTEL_H
