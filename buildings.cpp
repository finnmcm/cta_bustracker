//
// A collection of buildings in the Open Street Map.
//
// Finn McMillan
// Northwestern University
// CS 21
//
// 
//
#include "buildings.h"
#include "osm.h"
#include "tinyxml2.h"
#include <cassert>

using namespace std;
using namespace tinyxml2;

Buildings::Buildings(XMLDocument& xmldoc)
{
    XMLElement* osm = xmldoc.FirstChildElement("osm");
    assert(osm != nullptr);
    XMLElement* way = osm->FirstChildElement("way");
    //while there are still more ways to be read, parse them
    while(way != nullptr){
        if (osmContainsKeyValue(way, "building", "university")){
            assert(way != nullptr);
            const XMLAttribute* attrId = way->FindAttribute("id");
            assert(attrId != nullptr);
            long long id = attrId->Int64Value();

            string name = osmGetKeyValue(way, "name");
            string streetAddr = osmGetKeyValue(way, "addr:housenumber")
                + " " + osmGetKeyValue(way, "addr:street");

            Building B = Building(id, name, streetAddr);
            XMLElement* nd = way->FirstChildElement("nd");
            //fetch all perimeter nodes for the given building
            while(nd != nullptr){
                const XMLAttribute* ndref = nd->FindAttribute("ref");
                assert(ndref != nullptr);

                long long id = ndref->Int64Value();

                B.add(id);
                nd = nd->NextSiblingElement("nd");
            }
            this->osmBuildings.push_back(B);
    }
    way = way->NextSiblingElement("way");
}

}
int Buildings::getNumOsmBuildings(){
    return this->osmBuildings.size();
}
void Buildings::print(){
    for(Building b : this->osmBuildings){
        cout << b.ID << ": " << b.Name << ", " << b.StreetAddress << endl;
    }
}
bool Buildings::findAndPrint(string& name, Nodes& nodes, BusStops& busStops, CURL* curl){
    bool found = false;
    //iterate through all buildings on campus, stored in Buildings struct
    for(Building &b : this->osmBuildings){
        //if building is what we're looking for, get its data
        if(b.Name.find(name) != string::npos){
            found = true;
            b.print(nodes);
            pair<double, double> P = b.getLocation(nodes);
            pair<BusStop, BusStop> stops = busStops.findClosestStops(P, nodes);
            BusStop north = stops.first;
            BusStop south = stops.second;
            string southQuery = "http://ctabustracker.com/bustime/api/v2/getpredictions?key=dTDRKPRkafGaWYKcP4NtgGviN&rt=" + to_string(south.busRoute) + "&stpid=" + to_string(south.stopID) + "&format=json";
            string northQuery = "http://ctabustracker.com/bustime/api/v2/getpredictions?key=dTDRKPRkafGaWYKcP4NtgGviN&rt=" + to_string(north.busRoute) + "&stpid=" + to_string(north.stopID) + "&format=json";
            string southResponse;
            string northResponse;
            cout << "Closest southbound bus stop:" << endl;
            cout << "  " << south.stopID << ": " << south.stopName << ", bus #" << south.busRoute << ", "<< south.stopLocation;
            cout << ", " << distBetween2Points(south.coordinates.first, south.coordinates.second, P.first, P.second) << " miles" << endl;
            if(callWebServer(curl, southQuery, southResponse)){
                busStops.printBusPredictions(southResponse);
            }
            else{
                cout << "  <<bus predictions unavailable, call failed>>" << endl;
            }
          
            cout << "Closest northbound bus stop:" << endl;
            cout << "  " << north.stopID << ": " << north.stopName << ", bus #" << north.busRoute << ", "<< north.stopLocation;
            cout << ", " << distBetween2Points(north.coordinates.first, north.coordinates.second, P.first, P.second) << " miles" << endl;
            if(callWebServer(curl, northQuery, northResponse)){
                busStops.printBusPredictions(northResponse);
            }
            else{
                cout << "  <<bus predictions unavailable, call failed>>" << endl;
            }
        }
    }
    return found;
}