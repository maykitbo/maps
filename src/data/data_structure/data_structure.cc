#include "data_structure.h"


using namespace maykitbo::maps;

using json_t = OsmData::json_t;


OsmData::OsmData(json_t&& data)
    : data_(data) {}


const json_t& OsmData::getFeatures()
{
    return data_["features"];
}
