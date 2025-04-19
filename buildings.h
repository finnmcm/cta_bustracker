//
// A collection of buildings in the Open Street Map.
//
// Finn McMillan
// Northwestern University
// CS 21
//
// Original author: Prof. Joe Hummel
//
#pragma once
#include <vector>
#include "building.h"
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;
//
// Buildings
//
// Takes an xmldocument OpenStreetMap and constructs a vector of all buildings on Northwestern's campus
// using the Building class
//
class Buildings {
    public:
    vector<Building> osmBuildings;
    //CONSTRUCTOR:
    Buildings(XMLDocument& xmldoc);

    //accessors / getters
    int getNumOsmBuildings();
};