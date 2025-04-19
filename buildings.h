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
#include <iostream>
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

    //prints all buildings in the osmBuildings vector
    void print();

    //find and print matching buildings
    bool findAndPrint(string& name, Nodes& nodes);
};