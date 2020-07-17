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
        // 1 = motorcycle, 2 = compact, 3 = large
        int spot_type;
        // 1 = motorcycle, 2 = car, 3 = bus
        int type;

        Vehicle(int type){
            spot_type = type;
        }
};

class Motorcycle : public Vehicle{
    public:
        
    
};

class Car : public Vehicle{
    public:

};

class Bus : public Vehicle{
    public:  
        
};

class ParkingSpot{
    private:
        int spot_type;

    public:
        ParkingSpot(int type){
            spot_type = type;
        }

        bool fits_vehicle(int vehicle_type){
            if(spot_type >= vehicle_type){
                return true;
            }
            return false;
        }

};

class ParkingLot{
    private:
        int nLevels;


    public:
        ParkingLot(int nLevels){
            nLevels = nLevels;
        }

        void print_level(){
            for(int i = 0; i < nLevels; i++){
                
            }
        }

        void init_vehicles(){

        }

        bool park(int vehicle_type, int nSpots){
            
        }

};  