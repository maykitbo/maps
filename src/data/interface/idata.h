#pragma once


#include "types/line.h"
#include "types/polygon.h"
#include "postgis_connector.h"


namespace maykitbo::maps
{


class IData
{
    public:
        IData();
        void connect(const std::string& conn_str);
    
    private:
        PostGISConnector pgc_;  
};


} // namespace maykitbo::maps