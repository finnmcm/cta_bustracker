//
// A program to find buildings on the Northwestern campus and their corresponding OpenStreetMap
// nodes, as well as its ID and address
//
// Finn McMillan
// Northwestern University
// CS 211
// 
using namespace std;
#include <string>
#include <iostream>
#include "tinyxml2.h"
#include "building.h"
#include "busstops.h"
#include "busstop.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "buildings.h"
#include "curl_util.h"
using namespace tinyxml2;

int main(){
    //Initialize CURL
    CURL* curl = curl_easy_init();
    if (curl == nullptr) {
        cout << "**ERROR:" << endl;
        cout << "**ERROR: unable to initialize curl library" << endl;
        cout << "**ERROR:" << endl;
        return 0;
}
    XMLDocument xmldoc;
    

    cout << "** NU open street map **" << endl;
    string filename;
    cout << endl;
    cout << "Enter map filename>" << endl;
    getline(cin, filename);
    //if invalid file, exit program
    if (!osmLoadMapFile(filename, xmldoc)){
        return 0;
    }
    else{
        //create + initialize Nodes and Buildings classes to retrieve all nodes and buildings from OSM
        Nodes nodes = Nodes(xmldoc);
        Buildings buildings = Buildings(xmldoc);
        BusStops busStops = BusStops("bus-stops.txt");
        cout << "# of nodes: " << nodes.getNumOsmNodes() << endl;
        cout << "# of buildings: " << buildings.getNumOsmBuildings() << endl;
        cout << "# of bus stops: " << busStops.getNumBusStops() << endl;
        cout << endl;

        string command = "";
        //enter while loop where users can lookup names or partial names of buildings and see their corresponding nodes + building info
        while(true){
            cout << "Enter building name (partial or complete), or * to list, or @ for bus stops, or $ to end>" << endl;
            getline(cin, command);
            //list all buildings 
            if(command == "*"){
                buildings.print();
            }
            else if(command == "@"){
                busStops.print();
            }
            //exit program
            else if(command == "$"){
                break;
            }
            else{
                bool found = buildings.findAndPrint(command, nodes, busStops, curl);
                //if building is not found, let the user know
                if(!found){
                    cout << "No such building" << endl;
                }
            }
        }
        //clean up curl
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        cout << endl;
        cout << "** Done **" << endl;
        return 0;
    }
}