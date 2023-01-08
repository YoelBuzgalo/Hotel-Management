#include "Booking.h"
#include "Customer.h"
#include <ctime>
#include <string>
#include <iostream>

using namespace std;

Booking::Booking(Customer* newCustomerIndex, int newBookingIndex, string newCheckInDate, string newCheckOutDate, int amount, Room* selectedRoom)
:customerID(newCustomerIndex),
bookingID(newBookingIndex),
checkInDate(this->convertToTimestamp(newCheckInDate)),
checkOutDate(this->convertToTimestamp(newCheckOutDate)),
amountOfPeople(amount),
room(selectedRoom)
{

}

Customer* Booking::getCustomerID(){
    return this->customerID;
}

int Booking::getBookingID(){
    return this->bookingID;
}

int Booking::getCost(){
    return this->room->getRoomTypePrices();
}

long long Booking::getCheckInDate(){
    return this->checkInDate;
}

long long Booking::getCheckOutDate(){
    return this->checkOutDate;
}

long long Booking::convertToTimestamp(string date) {
    // Parse the input string to extract the month, day, and year
    int month, day, year;
    sscanf(date.c_str(), "%d/%d/%d", &month, &day, &year);

    // Convert the date to a tm struct
    struct tm tm;
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;
    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0;
    tm.tm_isdst = -1;

    // Convert the tm struct to a unix timestamp
    return mktime(&tm);
}

string Booking::convertToDate(long long timestamp) {
    // Convert the timestamp to a tm struct
    time_t time = timestamp;
    struct tm *tm = localtime(&time);

    // Convert the tm struct to a string in the form "MM/DD/YYYY"
    char buffer[256];
    strftime(buffer, 256, "%m/%d/%Y", tm);
    return buffer;
}

void Booking::setAmountOfPeople(int amount){
    this->amountOfPeople = amount;
}

int Booking::getAmountOfPeople(){
    return this->amountOfPeople;
}

string Booking::bookingDescription(){
    return "Booking No#: " + to_string(this->getBookingID()+1) + "\t" +
    this->room->roomDescription() + "\n" + to_string(this->getAmountOfPeople()) + " People, from " +
    this->convertToDate(this->checkInDate) + " to " + this->convertToDate(this->checkOutDate) + "\n\n";
}
