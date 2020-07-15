/*
Author: John Furlong
Date: June 12, 2020
Description: Parking Lot
    Design a parking lot using object oriented principles.
    Assume the following:
        - The parking lot has multiple levels. Each level has multiple rows of spots.
        - The parking lot can park cars, buses, and motorcycles
        - The parking lot has motorcycle spots, compact spots, and large spots.
        - A motorcycle can park in any spot
        - A car can park in either a single compact spot, or a single large spot. 
        - A bus can park only in five large spots that are consecutive and within the same row.
*/
#include <iostream>
#include <vector>
using namespace std;

class Vehicle{
    private:
        
    public:
        Vehicle(){
            
        }
};

class Motorcycle : public Vehicle{
    private:
        int size;
    
};

class ParkingSpot{
    private:

    public:
        ParkingSpot(){

        }

};