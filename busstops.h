/*busstops.h*/

//
// Contains all Bus stops from the CSV file
// 
// Finn McMillan
// Northwestern University
// CS 211
// 
#pragma once

#include <vector>
#include "busstop.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <utility>
#include "dist.h"
#include "nodes.h"
#include "json.hpp"
using namespace std;
using json = nlohmann::json;
//
// BusStops
//
// Takes a CSV file of all bus stops and converts them into BusStop objects, storing them 
// in a class vector
//
class BusStops {
    public:
    //internal vector of all busstops
    vector<BusStop> busStops;
    //CONSTRUCTOR:
    BusStops(string filename);
    //print all bus stops
    void print();
    //find and print any available bus predictions
    void printBusPredictions(string response);
    //locate closest bus stops to the given location
    pair<BusStop, BusStop> findClosestStops(pair<double, double> location, Nodes& nodes);

};