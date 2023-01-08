#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>

using namespace std;

class Room
{
    public:
        Room(int type);
        int getRoomTypePrices();
        int getRoomTypeCapacity();
        vector <long long> StartDate;
        vector <long long> EndDate;
        bool checkAvailability(long long CheckStart, long long CheckEnd);
        string roomDescription();


    protected:

    private:
        int roomType;

};

#endif // ROOM_H
