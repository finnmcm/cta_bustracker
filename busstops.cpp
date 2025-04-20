/*busstops.cpp*/

//
// A Bus Stop from the CSV file
// 
// Finn McMillan
// Northwestern University
// CS 211
// 
#include "busstops.h"
using namespace std;

BusStops::BusStops(string filename)
{
    ifstream file;
    file.open(filename);
    if(file.fail()){
        cout << "failed to read CSV file";
        return;
    }
    while(true){
        string line;
        getline(file, line);
        if(file.fail()){
            break;
        }
        stringstream parser(line);
        string id_str, route_str, stopname, direction, location, lat_str, lon_str;
        getline(parser, id_str, ',');
        getline(parser, route_str, ',');
        getline(parser, stopname, ',');
        getline(parser, direction, ',');
        getline(parser, location, ',');
        getline(parser, lat_str, ',');
        getline(parser, lon_str, ',');

        int stopID = stoi(id_str);
        int busRoute = stoi(route_str);
        double lat = stod(lat_str);
        double lon = stod(lon_str);
        pair<double, double> coordinates = make_pair(lat, lon);
        BusStop b = BusStop(stopID, busRoute, stopname, direction, location, coordinates);
        this->busStops.push_back(b);
        
    }
}
void BusStops::print(){
    sort(this->busStops.begin(), this->busStops.end(), [](BusStop& a, BusStop& b){
        return a.stopID < b.stopID;
    });
    for(BusStop& b : this->busStops){
        b.print();
    }
}
pair<BusStop, BusStop> BusStops::findClosestStops(Building& b, Nodes& nodes){
    pair<double, double> buildingLocation = b.getLocation(nodes);
    BusStop* closestNorthbound = nullptr;
    BusStop* closestSouthbound = nullptr;
    double northboundDist = 10000.0;
    double southboundDist = 10000.0;
    for(BusStop& b : this->busStops){
        if(b.directionOfTravel == "Northbound"){
            if(closestNorthbound == nullptr){
                closestNorthbound = &b;
                northboundDist = distBetween2Points(b.coordinates.first, b.coordinates.second, buildingLocation.first, buildingLocation.second);
            }
            else{
                double dist = distBetween2Points(b.coordinates.first, b.coordinates.second, buildingLocation.first, buildingLocation.second);
                if(dist < northboundDist){
                    closestNorthbound = &b;
                    northboundDist = dist;
                }
            }
        }
        else if(b.directionOfTravel == "Southbound"){
            if(closestSouthbound == nullptr){
                closestSouthbound = &b;
                southboundDist = distBetween2Points(b.coordinates.first, b.coordinates.second, buildingLocation.first, buildingLocation.second);
            }
            else{
                double dist = distBetween2Points(b.coordinates.first, b.coordinates.second, buildingLocation.first, buildingLocation.second);
                if(dist < southboundDist){
                    closestSouthbound = &b;
                    southboundDist = dist;
                }
            }
        }
    }
    return make_pair(*closestNorthbound, *closestSouthbound);
    
}