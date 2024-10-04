#include "tune.h"


#include "connector.h"
#include "config.h"

using namespace maykitbo::maps;
using namespace db;

/*
        0: osm_id
        1: z_order
        2: way_area
        3: way
        4: draw_type
        5: admin_level
        6: aerialway
        7: aeroway
        8: amenity
        9: area
        10: barrier
        11: bicycle
        12: brand
        13: bridge
        14: boundary
        15: building
        16: construction
        17: covered
        18: culvert
        19: cutting
        20: denomination
        21: disused
        22: embankment
        23: foot
        24: generator:source
        25: harbour
        26: highway
        27: historic
        28: horse
        29: intermittent
        30: junction
        31: landuse
        32: layer
        33: leisure
        34: lock
        35: man_made
        36: military
        37: motorcar
        38: name
        39: natural
        40: office
        41: oneway
        42: operator
        43: place
        44: population
        45: power
        46: power_source
        47: public_transport
        48: railway
        49: ref
        50: religion
        51: route
        52: service
        53: shop
        54: sport
        55: surface
        56: toll
        57: tourism
        58: tower:type
        59: tracktype
        60: tunnel
        61: waterway
        62: wetland
        63: width
        64: wood
        65: water
        66: access
        67: addr:housename
        68: addr:housenumber
        69: addr:interpolation
*/

int main()
{
    // std::unordered_map<std::string, int> mapping;
    // std::unordered_map<std::string, int> types;
    
    // analise(mapping, types, "highway", DBStruct::ROAD_TABLE);


    // Connector pgc(Conf::postgis);
    // pgc.executeQuery("ALTER TABLE planet_osm_roads ADD COLUMN draw_type INTEGER NOT NULL DEFAULT -1;");



    // auto tt = readPolygonMapping("src/data/tune_db/lines.ntoc");
    // std::unordered_map<std::string, int> mapping =
    //     std::move(tt.second);
    // std::unordered_map<std::string, int> types =
    //     std::move(tt.first);


    // analise(mapping, types, "highway", DBStruct::ROAD_TABLE);


    // // createJson(DBStruct::POLYGON_TABLE);


    // auto tt2 = readPolygonMapping("src/data/tune_db/railway.ntoc");
    // std::unordered_map<std::string, int> mapping2 =
    //     std::move(tt2.second);

    // tuneMaster(DBStruct::ROAD_TABLE, "highway", mapping);



    // updateBoundingBoxes(DBStruct::POLYGON_TABLE, 50000);
    

    Connector pgc(Conf::postgis);
    auto R = pgc.executeQuery("CREATE INDEX idx_way_area ON planet_osm_polygon (way_area); "
                     "ANALYZE planet_osm_polygon;");
    
    std::cout << R.size() << "\n";
    for (auto C : R)
    {
        for (auto F : C)
        {
            std::cout << F.name() << "\t" << F.c_str() << "\n";
        }
    }

    return 0;
}