/*busstops.cpp*/

//
// All BusStops from the CSV file
// 
// Finn McMillan
// Northwestern University
// CS 211
// 
#include "busstops.h"
#include <stdexcept>
using namespace std;

BusStops::BusStops(string filename)
{
    ifstream file;
    file.open(filename);
    if(file.fail()){
        cout << "failed to read CSV file";
        return;
    }
    //while the CSV bus stops file still has content, parse each line to extract bus stop traits
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
        //convert necessary attributes to numbers
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
    //first, sort bus stops by stop ID
    sort(this->busStops.begin(), this->busStops.end(), [](BusStop& a, BusStop& b){
        return a.stopID < b.stopID;
    });
    //iterate through busStops internal vector and print each one
    for(BusStop& b : this->busStops){
        b.print();
    }
}
pair<BusStop, BusStop> BusStops::findClosestStops(pair<double, double> location, Nodes& nodes){
    //set originally to nullptr before initalization
    BusStop* closestNorthbound = nullptr;
    BusStop* closestSouthbound = nullptr;
    double northboundDist = 10000.0;
    double southboundDist = 10000.0;
    //iterate through busStops vector to find closest stops
    for(BusStop& b : this->busStops){
        //ONLY CHECKING FOR NORTH AND SOUTHBOUND BUSES
        if(b.directionOfTravel == "Northbound"){
            if(closestNorthbound == nullptr){
                closestNorthbound = &b;
                northboundDist = distBetween2Points(b.coordinates.first, b.coordinates.second, location.first, location.second);
            }
            else{
                double dist = distBetween2Points(b.coordinates.first, b.coordinates.second, location.first, location.second);
                if(dist < northboundDist){
                    closestNorthbound = &b;
                    northboundDist = dist;
                }
            }
        }
        else if(b.directionOfTravel == "Southbound"){
            if(closestSouthbound == nullptr){
                closestSouthbound = &b;
                southboundDist = distBetween2Points(b.coordinates.first, b.coordinates.second, location.first, location.second);
            }
            else{
                double dist = distBetween2Points(b.coordinates.first, b.coordinates.second, location.first, location.second);
                if(dist < southboundDist){
                    closestSouthbound = &b;
                    southboundDist = dist;
                }
            }
        }
    }
    //add * in return to convert back from pointer to object
    return make_pair(*closestNorthbound, *closestSouthbound);
    
}
void BusStops::printBusPredictions(string response){
    auto jsondata = json::parse(response);
    auto bus_response = jsondata["bustime-response"];
    auto predictions = bus_response["prd"];
    bool hasPrediction = false;
    //iterate through each map under the "prd" map to extract all vehicle predictions
    for(auto & M : predictions){
        hasPrediction = true;
        //check for any exceptions while reading predictions
        try {
            cout << "vehicle #" << stoi(M["vid"].get_ref<std::string&>()) << " on route " << stoi(M["rt"].get_ref<std::string&>()) << " travelling " << M["rtdir"].get_ref<std::string&>() << " to arrive in " << stoi(M["prdctdn"].get_ref<std::string&>()) << " mins" << endl;
        } catch (exception& e){
            cout << " error" << endl;
            cout << " malformed CTA response, prediction unavailable";
            cout << " (error: " << e.what() << ")" << endl;
        }
    }
    if(!hasPrediction){
        cout << "  <<no predictions available>>" << endl;
    }
}