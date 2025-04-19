/*building.cpp*/

//
// A building in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211
// 

#include "building.h"

using namespace std;


//
// constructor
//
Building::Building(long long id, string name, string streetAddr)
  : ID(id), Name(name), StreetAddress(streetAddr)
{
  // vector is default initialized by its constructor
}

//
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}
void Building::print(Nodes& nodes){

  pair<double, double> P = this->getLocation(nodes);
  cout << this->Name << endl;
  cout << "Address: " << this->StreetAddress << endl;
  cout << "Building ID: " << this->ID << endl;
  cout << "# perimeter nodes: " << this->NodeIDs.size() << endl;
  cout << "Location: " <<"(" << P.first << ", " << P.second << ")" << endl; 
  //iterate through all the node IDs of the building(s) and print them
/*  for(long long &id : this->NodeIDs){
      double lat;
      double lon;
      bool isEntrance;
       if(nodes.find(id, lat, lon, isEntrance)){
          cout << "  " << id << ": (" << lat << ", " << lon << ")"; 
       }
       if(isEntrance){
          cout << ", is entrance";
       }
       cout << endl;
  }*/
}
pair<double, double> Building::getLocation(Nodes& nodes){
  //iterate through all the node IDs of the building(s) and print them
  double avgLat = 0;
  double avgLon = 0;
  for(long long &id : this->NodeIDs){
      double lat;
      double lon;
      bool isEntrance;
       if(nodes.find(id, lat, lon, isEntrance)){
          avgLat += lat;
          avgLon += lon;
       }
  }
  avgLat = avgLat / this->NodeIDs.size();
  avgLon = avgLon / this->NodeIDs.size();
  return make_pair(avgLat, avgLon);
}

