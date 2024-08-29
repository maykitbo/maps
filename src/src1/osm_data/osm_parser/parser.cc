#include "parser.h"


using namespace maykitbo::maps;


json_t OsmParser::getJson(data_idx_t idx)
{
    std::ifstream f(OsmConfig::getDataPath(idx));
    return json_t::parse(f);
}


const json_t& OsmParser::getFeatures(const json_t& data)
{
    return data["features"];
}


std::vector<coord_t> OsmParser::getBbox(data_idx_t idx)
{
    std::vector<coord_t> bbox;
    std::ifstream f(OsmConfig::getDescriptionPath());
    for (data_idx_t k = 0; k < idx && f; ++k)
    {
        f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if (f.peek() != '\n' && f.peek() != EOF)
    {
        data_idx_t i = 0;
        f >> i;
        if (i != idx)
        {
            throw(std::invalid_argument("Invalid File description.txt"));
        }
        bbox.resize(4);
        f >> bbox[0] >> bbox[1] >> bbox[2] >> bbox[3];
    }
    return bbox;
}


bool OsmParser::isNode(const json_t& feature)
{
    return getType(feature) == "node";
}


bool OsmParser::isWay(const json_t& feature)
{
    return getType(feature) == "way";
}


std::string OsmParser::getType(const json_t& feature)
{
    return feature["properties"]["type"];
}


feat_idx_t OsmParser::getId(const json_t& feature)
{
    return feature["properties"]["id"];
}


coord_t OsmParser::getLat(const json_t& feature)
{
    return feature["geometry"]["coordinates"][1];
}


coord_t OsmParser::getLon(const json_t& feature)
{
    return feature["geometry"]["coordinates"][0];
}





