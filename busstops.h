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
#include "building.h"
#include "nodes.h"
using namespace std;
//
// BusStops
//
// Takes a CSV file of all bus stops and converts them into BusStop objects, storing them 
// in a class vector
//
class BusStops {
    public:
    vector<BusStop> busStops;
    //CONSTRUCTOR:
    BusStops(string filename);

    void print();
    pair<BusStop, BusStop> findClosestStops(Building& B, Nodes& nodes);
};