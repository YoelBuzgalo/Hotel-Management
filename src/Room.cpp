#include "Room.h"
#include <iostream>
#include <string>
#include <vector>

Room::Room(int type)
:roomType(type)
{

}

int Room::getRoomTypePrices(){
    switch (this->roomType){
        case 1:
            return 150; // Single Bed Room Costs $150
            break;
        case 2:
            return 200;// Double Bed Room Costs $200
            break;
        case 3:
            return 250; // Triple Bed Room Costs $250
            break;
        case 4:
            return 300; // Family Room (King Size Bed + 2 Single Beds) Costs $300
            break;
        default:
            return -1; // In case nothing matches, returns -1 for error handling.
            break;
    }
}

int Room::getRoomTypeCapacity(){
    switch (this->roomType){
        case 1:
            return 1;
            break;
        case 2:
            return 2;
            break;
        case 3:
            return 3;
            break;
        case 4:
            return 4;
            break;
        default:
            return -1;
            break;
    }
}

bool Room::checkAvailability(long long CheckStart, long long CheckEnd){
    if (this->StartDate.size() == 0){
        return true;
    }

    for(int i=0; i < this->StartDate.size(); i++){
        long long BookStart = this->StartDate[i];
        long long BookEnd = this->EndDate[i];
        if ((BookStart <= CheckStart && CheckStart <= BookEnd)
            ||(BookStart <= CheckEnd && CheckEnd <= BookEnd)
            ||(CheckStart <= BookStart && BookStart <= CheckEnd)
            ||(CheckStart <= BookEnd && BookEnd <= CheckEnd)
            ){
                return false;
            }
    }
    return true;
}

string Room::roomDescription(){
    switch (this->roomType){
        case 1:
            return "Single Bed Room, Costs $150";
            break;
        case 2:
            return "Double Bed Room, Costs $200";
            break;
        case 3:
            return "Triple Bed Room, Costs $250";
            break;
        case 4:
            return "Family Room (King Size Bed + 2 Single Beds), Costs $300";
            break;
        default:
            return "Invalid room";
            break;
    }
}
