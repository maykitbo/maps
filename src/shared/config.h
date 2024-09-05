#pragma once


#include <string>


namespace maykitbo::maps
{


struct Conf
{
    inline static const std::string postgis = R"(
        dbname = ***
        user = ***
        password = ***
        hostaddr = ***
        port = ***
    )";
};


} // namespace maykitbo::maps