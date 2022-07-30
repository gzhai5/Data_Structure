#include "airline.h"
#include <math.h>
using namespace std;

airline::airline(airport* s, airport* d) {
    source_ = s;
    destination_ = d;
    distance=this->calculateDistance();
}

airline::~airline() {
    if (source_) {
	delete source_;
    }
    if (destination_) {
	delete destination_;
    }
}

void airline::print() {
    std::cout << "This flight is from " << source_->name_ << " to " << destination_->name_ << std::endl;
}

/* reference from Haversine formula
   https://stackoverflow.com/questions/27928/calculate-distance-between-two-latitude-longitude-points-haversine-formula
   the units of the distance come in kilometres (km)
*/
double airline::calculateDistance(double latitude1,double longitude1,double latitude2,double longitude2) {
    if((latitude1==latitude2) && (longitude1==longitude2)) {
        return 0;
    }
    double distance; //convert all lon and lat from degree to radius
    double lat1=latitude1*((M_PI)/180);//deg2rad
    double lat2=latitude2*((M_PI)/180);
    double lon1=longitude1*((M_PI)/180);
    double lon2=longitude2*((M_PI)/180);

    double radius=6378; //radius of earth

    //Haversine Formula
    double dLat=lat2-lat1;  
    double dLon=lon2-lon1;
    distance=pow(sin(dLat/2),2)+cos(lat1) *cos(lat2)* pow(sin(dLon/2),2);
    distance=2* asin(sqrt(distance));
    distance*=radius;
    
    return distance;
}

double airline::calculateDistance() {
    return calculateDistance(source_->latitude_, source_->longitude_, destination_->latitude_, destination_->longitude_);
}



double airline::calculateDistance(airport* source, airport* destination){
    double latitude1 = source -> latitude_;
    double latitude2 = destination -> latitude_;
    double longitude1 = source -> longitude_;
    double longitude2 = destination -> longitude_;
    
    return calculateDistance(latitude1, longitude1, latitude2, longitude2);
}
