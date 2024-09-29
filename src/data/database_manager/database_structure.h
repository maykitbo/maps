#pragma once


#include <string>
#include <unordered_map>
#include <vector>

#include "types.h"


namespace maykitbo::maps
{


class DBStruct
{
    public:
        inline const static std::string WAY_WKB_COL = "wkb_way";
        inline const static std::string DRAW_TYPE_COL = "draw_type";
        inline const static std::string ID_COL = "osm_id";
        inline const static std::string TEXT_WAY_COL = "text_way";
        inline const static std::string WAY_COL = "way";
        inline const static std::string WAY_AREA_COL = "way_area";

        // inline const static std::string WAY_AREA_COL = "way_area";
        // inline const static std::string WAY_AREA_COL = "way_area";
        // inline const static std::string WAY_AREA_COL = "way_area";


        const static int SRID_OUT = 4326;
        const static int SRID_IN = 3857;
        // inline const static std::string ADDR_COL = "[addr:]";

        inline const static std::string POLYGON_TABLE = "planet_osm_polygon";
        inline const static std::string LINE_TABLE = "planet_osm_line";

        // inline static std::unordered_map<>

        inline const static std::vector<std::string> COLUMNS =
        {
            "aerialway", "aeroway", "amenity", "area", "barrier", "bicycle", "brand",
            "bridge", "boundary", "building", "construction", "covered", "culvert",
            "cutting", "denomination", "disused", "embankment", "foot", "generator:source",
            "harbour", "highway", "historic", "horse", "intermittent", "junction", "landuse",
            "layer", "leisure", "lock", "man_made", "military", "motorcar", "name", "natural",
            "office", "oneway", "operator", "place", "population", "power", "power_source",
            "public_transport", "railway", "ref", "religion", "route", "service", "shop",
            "sport", "surface", "toll", "tourism", "tower:type", "tracktype", "tunnel",
            "waterway", "wetland", "width", "wood", "water", "access"
        };

        inline static std::string ALL_INFO_COLUMNS =
            " aerialway, aeroway, amenity, area, barrier, bicycle, brand, "
            "bridge, boundary, building, construction, covered, culvert, "
            "cutting, denomination, disused, embankment, foot, \"generator:source\", "
            "harbour, highway, historic, horse, intermittent, junction, landuse, "
            "layer, leisure, lock, man_made, military, motorcar, name, \"natural\", "
            "office, oneway, operator, place, population, power, power_source, "
            "public_transport, railway, ref, religion, route, service, shop, "
            "sport, surface, toll, tourism, \"tower:type\", tracktype, tunnel, "
            "waterway, wetland, width, wood, water, access";
        
        inline static std::string ALL_INFO_COLUMNS_POLYGON =
            " aerialway, aeroway, amenity, area, barrier, bicycle, "
            "bridge, boundary, building, construction, covered, culvert, "
            "cutting, denomination, disused, embankment, foot, \"generator:source\", "
            "harbour, highway, historic, horse, intermittent, junction, landuse, "
            "layer, leisure, lock, man_made, military, motorcar, \"natural\", "
            "office, oneway, operator, place, population, power, power_source, "
            "public_transport, railway, ref, religion, route, service, shop, "
            "sport, surface, toll, tourism, \"tower:type\", tracktype, tunnel, "
            "waterway, wetland, width, wood, water, access";
        
        // inline static std::vector<std::string> POLYGON_DRAW_INFO_COLUMNS =
        // {
        //     "access", "aerialway", "aeroway", "amenity", "area", "barrier", "bicycle",
        //     "boundary", "bridge", "building", "construction", "culvert", "cutting",
        //     "denomination", "disused", "embankment", "foot", "generator:source",
        //     "harbour", "highway", "historic", "horse", "intermittent", "junction",
        //     "landuse", "leisure", "lock", "man_made", "military", "motorcar",
        // };

        // inline static std::vector<std::string> POLYGON_NAME_COLUMNS =
        // {
        //     "brand", "layer", "name"
        // };
};


} // namespace maykitbo::maps
