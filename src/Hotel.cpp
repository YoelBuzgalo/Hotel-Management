#include "Hotel.h"
#include "Customer.h"
#include "Room.h"
#include "Booking.h"
#include <iostream>
#include <string>

using namespace std;

Hotel::Hotel()
{
    this->CurrentLoggedInCustomer = nullptr;

    Room *room1 = new Room(1);
    Room *room2 = new Room(2);
    Room *room3 = new Room(3);
    Room *room4 = new Room(4);

    this->RoomList.push_back(room1);
    this->RoomList.push_back(room2);
    this->RoomList.push_back(room3);
    this->RoomList.push_back(room4);

}

void Hotel::start(){

    int input = -1;

    do{
        cout << "------- Hotel of Yoel -------" << endl
             << "Welcome, what do you want to do? " << endl
             << "1 - Login" << endl
             << "2 - Create Account" << endl
             << "3 - Log out" << endl
             << "4 - Book a room" << endl
             << "5 - Manage my booking" << endl
             << "6 - Exit" << endl;
        cin >> input;

        switch(input){
            case 1: //handle login
                if (this->CurrentLoggedInCustomer != nullptr){
                    cout << "You are already logged in!" << endl;
                    break;
                }
                this->handleLogin();
                break;
            case 2: //create account
                if (this->CurrentLoggedInCustomer != nullptr){
                    cout << "You are already logged in! Please log out first to create an account." << endl;
                    break;
                }
                this->handleCreateAccount();
                break;
            case 3: //Log out
                if (this->CurrentLoggedInCustomer != nullptr){
                    this->handleLogout();
                    break;
                }
                cout << "You cannot log out since you aren't logged in yet." << endl;
                break;
            case 4: //Add booking
                if (this->CurrentLoggedInCustomer != nullptr){
                    this->createReservationBooking();
                    break;
                }
                cout << "Please log in first before creating a reservation." << endl;
                break;
            case 5: //View or delete booking
                if (this->CurrentLoggedInCustomer != nullptr){
                    this->viewReservationBooking();
                }
                break;
            case 6: //Exit program
                break;
            default: //Error
                cerr << "Error, no matched input entered!" << endl;
                break;
        }
    }while(input != 6);
}

void Hotel::handleCreateAccount(){

    string name;
    string password;

    cout << "Let's create your account, please enter your name: " << endl;
    cin.ignore();
    getline(cin, name);
    cout << "Great! Please enter your preferred password now: " << endl;
    cin.ignore();
    getline(cin, password);

    Customer* foundCustomer = this->findUser(name);

    if(foundCustomer != nullptr){
        cout << "User already exists!" << endl;
        return;
    }

    Customer* newCustomer = new Customer(name, password);
    this->CustomerList.push_back(newCustomer);
    this->CurrentLoggedInCustomer = newCustomer;

    cout << "Okay great! You're now logged in!" << endl;
}

void Hotel::handleLogin(){

    string name;
    string password;

    cout << "Please enter your name: " << endl;
    cin.ignore();
    getline(cin, name);
    cout << "Please enter your password now: " << endl;
    cin.ignore();
    getline(cin, password);

    Customer* foundCustomer = this->findUser(name);

    if (foundCustomer == nullptr){
        cout << "Invalid name, no user found!" << endl;
        return;
    }

    if (foundCustomer->getCustomerPassword() != password){
        cout << "Invalid password" << endl;
        return;
    }

    this->CurrentLoggedInCustomer = foundCustomer;

    cout << "Hello, you're logged in as " << foundCustomer->getCustomerName() << endl;
}

void Hotel::handleLogout(){
    this->CurrentLoggedInCustomer = nullptr;
    cout << "Okay you're logged out!" << endl;
}

Customer* Hotel::findUser(string name){

    Customer* foundCustomer = nullptr;

    for (int i=0; i < this->CustomerList.size(); i++){
        Customer* currentCustomer = this->CustomerList[i];
        if (currentCustomer->getCustomerName() == name){
            foundCustomer = currentCustomer;
            break;
        }
    }
    return foundCustomer;
}

void Hotel::createReservationBooking(){

    string amountInput;
    int amountInputInteger;
    string checkInDateInput;
    string checkOutDateInput;
    Customer* customerIndex = this->CurrentLoggedInCustomer;
    int bookingIndex = this->BookingList.size();

    cout << "Okay, lets create a reservation!" << endl
         << "How many people will you be? Enter only in numbers (0-9)" << endl;
    cin.ignore();
    getline(cin, amountInput);
    amountInputInteger = stoi(amountInput);
    cout << "When will you be checking in? Enter only in the format of MM/DD/YYYY" << endl;
    getline(cin, checkInDateInput);
    cout << "When will you be checking out? Enter only in the format of MM/DD/YYYY" << endl;
    getline(cin, checkOutDateInput);

    vector <Room*> matching;

    long long convertedStartDate = this->convertToTimestamp(checkInDateInput);
    long long convertedEndDate = this->convertToTimestamp(checkOutDateInput);

    for(int i=0; i < this->RoomList.size(); i++){
        Room* current = this->RoomList[i];
        if (amountInputInteger <= current->getRoomTypeCapacity()){
            if(current->checkAvailability(convertedStartDate, convertedEndDate)){
                matching.push_back(current);
            }
        }
    }

    if (matching.size() == 0){
        cout << "No rooms matched for your criteria" << endl;
        return;
    }

    int input;

    cout << "Here's our list of matching availability: " << endl;
    for(int i=0; i < matching.size(); i++){
        cout << (i+1) << " - " << matching[i]->roomDescription() << endl;
    }
    cout << "Enter -1 to Cancel" << endl;
    cin >> input;

    if (input == -1){
        return;
    }

    Room* selectedRoom = matching[input-1];
    selectedRoom->StartDate.push_back(convertedStartDate);
    selectedRoom->EndDate.push_back(convertedEndDate);

    Booking* newBooking = new Booking(customerIndex, bookingIndex, checkInDateInput, checkOutDateInput, amountInputInteger, selectedRoom);

    this->BookingList.push_back(newBooking);


}

void Hotel::viewReservationBooking(){
    if(this->BookingList.size() == 0){
        cout << "You have no booking!" << endl;
        return;
    }
    vector <Booking*> foundBooking;
    for(int i=0; i < this->BookingList.size(); i++){
        if(this->CurrentLoggedInCustomer == this->BookingList[i]->getCustomerID()){
            foundBooking.push_back(this->BookingList[i]);
        }
    }
    for(int i=0; i < foundBooking.size(); i++){
        cout << foundBooking[i]->bookingDescription() << endl;
    }
}

long long Hotel::convertToTimestamp(string date){
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

string Hotel::convertToDate(long long timestamp){
    // Convert the timestamp to a tm struct
    time_t time = timestamp;
    struct tm *tm = localtime(&time);

    // Convert the tm struct to a string in the form "MM/DD/YYYY"
    char buffer[256];
    strftime(buffer, 256, "%m/%d/%Y", tm);
    return buffer;
}
