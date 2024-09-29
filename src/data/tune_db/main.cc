#include "tune.h"


using namespace maykitbo::maps;

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
    std::unordered_map<std::string, int> mapping;
    std::unordered_map<std::string, int> types;

    // auto tt = readPolygonMapping("src/data/tune_db/natural.ntoc");
    // std::unordered_map<std::string, int> mapping =
    //     std::move(tt.second);
    // std::unordered_map<std::string, int> types =
    //     std::move(tt.first);


    // analise(mapping, types, "place", "planet_osm_polygon");
    // realNatural(mapping);
    createJson(DBStruct::POLYGON_TABLE);

    

    return 0;
}