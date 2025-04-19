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
bool Buildings::findAndPrint(string& name, Nodes& nodes){
    bool found = false;
    //iterate through all buildings on campus, stored in Buildings struct
    for(Building &b : this->osmBuildings){
        //if building is what we're looking for, get its data
        if(b.Name.find(name) != string::npos){
            found = true;
            b.print(nodes);
        }
    }
    return found;
}