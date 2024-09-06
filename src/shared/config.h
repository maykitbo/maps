#pragma once


#include <string>


namespace maykitbo::maps
{


struct Conf
{
    inline static const std::string postgis = R"(
        dbname = osm_db
        user = postgres
        password = postgres
        hostaddr = 127.0.0.1
        port = 5432
    )";
};


} // namespace maykitbo::maps