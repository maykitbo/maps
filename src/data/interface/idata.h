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

        GeoJson fetch(const std::string& table, const bbox_s& bbox, int srid = 4326) const;
        // GeoJson fetchWithCache(const std::string& table, const bbox_s& bbox, int srid = 4326) const;
        GeoJson fetchRoads(const bbox_s& bbox, bool cache = true, int srid = 4326) const;
        GeoJson fetchPoints(const bbox_s& bbox, bool cache = true, int srid = 4326) const;
        GeoJson fetchPolygons(const bbox_s& bbox, bool cache = true, int srid = 4326) const;
        GeoJson fetchLines(const bbox_s& bbox, bool cache = true, int srid = 4326) const;

        const PostGISConnector& getConnector() const { return pgc_; }

        void listColumns(const std::string& table) const;
        void listTables() const;

    private:
        PostGISConnector pgc_;
};


} // namespace maykitbo::maps



