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
        inline const static std::string WAY_COL = "way";
        inline const static std::string WAY_AREA_COL = "way_area";

        const static int SRID = 3857;
        // inline const static std::string ADDR_COL = "[addr:]";

        inline const static std::string POLYGON_TABLE = "planet_osm_polygon";

        const static int LIMIT = 10000;
};


} // namespace maykitbo::maps
