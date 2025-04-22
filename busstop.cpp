/*busstop.cpp*/

//
// A Bus Stop from the CSV file
// 
// Finn McMillan
// Northwestern University
// CS 211
// 
#include "busstop.h"
using namespace std;

//
// constructor
//
BusStop::BusStop(int stopID, int busRoute, string stopName, string directionOfTravel, string stopLocation, pair<double, double> coordinates)
  : stopID(stopID), busRoute(busRoute), stopName(stopName), directionOfTravel(directionOfTravel), stopLocation(stopLocation), coordinates(coordinates)
{
  //nothing needed here
}
//print a bus stop (its data)
void BusStop::print(){
    cout << stopID << ": bus " << busRoute << ", " << stopName << ", " << directionOfTravel << ", " << stopLocation << ", location (" << coordinates.first << ", " << coordinates.second << ")" << endl;
}
