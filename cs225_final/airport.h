#pragma once
#include <string>
#include <iostream>

class airport {

    public:
    airport(unsigned id, std::string name, double latitude, double longitude);
    void print();

    /* The public data of airports, including an integer id, 3-letter abbr, and its coordinates*/
    unsigned id_;
    std::string name_;
    double latitude_;
    double longitude_;

};
