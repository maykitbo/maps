#pragma once


#include <nlohmann/json.hpp>

#include "postgis_connector.h"
#include "config.h"
#include "data_structure.h"


namespace maykitbo::maps
{


class IData
{
    public:
        IData(const std::string &connect_string = Conf::postgis);

        OsmData fetch(const std::string& table, const bbox_s& bbox, int srid = 4326);
        OsmData fetchRoads(const bbox_s& bbox, int srid = 4326);
        OsmData fetchPoints(const bbox_s& bbox, int srid = 4326);
        OsmData fetchPolygons(const bbox_s& bbox, int srid = 4326);

        void listColumns(const std::string& table);
        void listTables();

    private:
        PostGISConnector pgc_;
};


} // namespace maykitbo::maps



