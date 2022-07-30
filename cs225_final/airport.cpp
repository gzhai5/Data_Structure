# include "airport.h"

airport::airport(unsigned id, std::string name, double latitude, double longitude) {
    id_ = id;
    name_ = name;
    latitude_ = latitude;
    longitude_ = longitude;
}

void airport::print() {
    std::cout << "#" << id_ << " " << name_ << " is at (" << latitude_<< ", " <<longitude_ << ")" << std::endl;
}
