#pragma once


#include <string>

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

        const static int SRID_OUT = 4326;
        const static int SRID_IN = 3857;
        // inline const static std::string ADDR_COL = "[addr:]";

        inline const static std::string POLYGON_TABLE = "planet_osm_polygon";
        inline const static std::string LINE_TABLE = "planet_osm_line";
};


} // namespace maykitbo::maps
