#pragma once
#include <string>
#include <iostream>
#include <math.h>
#include "airport.h"
using namespace std;

class airline {

    public:
    airline(airport* s, airport* d);
    double calculateDistance();
    void print();
    ~airline();
    double distance;
    airport* source_;
    airport* destination_;

    private:
    double calculateDistance(double latitude1,double longitude1,double latitude2,double longitude2);
    double calculateDistance(airport* source, airport* destination);
    

};
