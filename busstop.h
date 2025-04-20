/*busstop.h*/

//
// A Bus Stop from the CSV file
// 
// Finn McMillan
// Northwestern University
// CS 211
// 
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "node.h"
#include "nodes.h"
#include <utility>


using namespace std;


//
// Bus Stop
//
// Defines a Bus Stop object, which contains the Stop ID,
// bus route, stop name, the direction of travel, location
// of the stop, and position in lat and lon
// 
//
class BusStop
{
public:
  int stopID;
  int busRoute;
  string stopName;
  string directionOfTravel;
  string stopLocation;
  pair<double, double> coordinates;

  //
  // constructor
  //
  BusStop(int stopID, int busRoute, string stopName, string directionOfTravel, string stopLocation, pair<double, double> coordinates);
  
    //print a bus stop
  void print();
};