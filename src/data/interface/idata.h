#pragma once


#include "postgis_connector.h"


namespace maykitbo::maps
{


class IData
{
    public:
        IData()
        {
            pgc.connect(
                "dbname = osm_db user = postgres password = postgres hostaddr = 127.0.0.1 port = 5432"
            );
        }
        PostGISConnector& operator()() { return pgc; }
        // ~IData();

        // void loadBbox(bbox_s bbox);


    private:
        PostGISConnector pgc;
};


} // namespace maykitbo::maps



