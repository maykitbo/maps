#pragma once


#include "postgis_connector.h"
#include "config.h"
#include "geojson_handler.h"


namespace maykitbo::maps
{


class IData
{
    public:
        IData(const std::string &connect_string = Conf::postgis);

        GeoJson fetch(const std::string& table, const bbox_s& bbox, int srid = 4326);
        GeoJson fetchRoads(const bbox_s& bbox, int srid = 4326);
        GeoJson fetchPoints(const bbox_s& bbox, int srid = 4326);
        GeoJson fetchPolygons(const bbox_s& bbox, int srid = 4326);

        void listColumns(const std::string& table);
        void listTables();

    private:
        PostGISConnector pgc_;
};


} // namespace maykitbo::maps



