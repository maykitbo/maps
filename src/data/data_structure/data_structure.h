#pragma once


#include <nlohmann/json.hpp>

#include "types.h"


namespace maykitbo::maps
{


class OsmData
{
    public:
        using json_t = nlohmann::json;

        OsmData(json_t&& data);
        const json_t& getFeatures();


    private:
        json_t data_;
};


} // namespace maykitbo::maps