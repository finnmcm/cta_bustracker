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
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "buildings.h"
using namespace tinyxml2;

int main(){
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
        cout << "# of nodes: " << nodes.getNumOsmNodes() << endl;
        cout << "# of buildings: " << buildings.getNumOsmBuildings() << endl;
        cout << endl << endl;

        string command = "";
        //enter while loop where users can lookup names or partial names of buildings and see their corresponding nodes + building info
        while(true){
            cout << "Enter building name (partial or complete), or * to list, or $ to end>" << endl;
            getline(cin, command);
            //list all buildings 
            if(command == "*"){
                for(Building b : buildings.osmBuildings){
                    cout << b.ID << ": " << b.Name << ", " << b.StreetAddress << endl;
                }
            }
            //exit program
            else if(command == "$"){
                break;
            }
            else{
                bool found = false;
                //iterate through all buildings on campus, stored in Buildings struct
                for(Building &b : buildings.osmBuildings){
                    //if building is what we're looking for, get its data
                    if(b.Name.find(command) != string::npos){
                        found = true;
                        cout << b.Name << endl;
                        cout << "Address: " << b.StreetAddress << endl;
                        cout << "Building ID: " << b.ID << endl;
                        cout << "Nodes: " << endl;
                        //iterate through all the node IDs of the building(s) and print them
                        for(long long &id : b.NodeIDs){
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
                        }
                    }
                }
                //if building is not found, let the user know
                if(!found){
                    cout << "No such building" << endl;
                }
            }
        }
        cout << endl;
        cout << "** Done **" << endl;
        cout << "# of calls to getID(): " <<Node::getCallsToGetID()<< endl;
        cout << "# of Nodes created: " <<Node::getCreated()<< endl;
        cout << "# of Nodes copied: " <<Node::getCopied()<< endl;
        return 0;
    }
}