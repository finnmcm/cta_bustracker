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