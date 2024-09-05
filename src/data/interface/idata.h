#pragma once


#include "postgis_connector.h"
#include "config.h"


namespace maykitbo::maps
{


class IData
{
    public:
        IData(const std::string &connect_string = Conf::postgis)
        {
            pgc.connect(connect_string);
        }
        PostGISConnector& operator()() { return pgc; }
        // ~IData();

        // void loadBbox(bbox_s bbox);


    private:
        PostGISConnector pgc;
};


} // namespace maykitbo::maps



