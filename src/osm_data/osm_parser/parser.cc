#include "parser.h"

nlohmann::json OsmParser::getJson(unsigned idx)
{
    std::ifstream f(OsmConfig::getDataPath(idx));
    return njson::parse(f);
}


std::vector<double> OsmParser::getBbox(unsigned idx)
{
    std::vector<double> bbox;
    std::ifstream f(OsmConfig::getDescriptionPath());
    for (int k = 0; k < idx && f; ++k)
    {
        f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    if (f.peek() != '\n' && f.peek() != EOF)
    {
        int i = 0;
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


bool OsmParser::isNode(const njson& feature)
{
    return getType(feature) == "node";
}


bool OsmParser::isWay(const njson& feature)
{
    return getType(feature) == "way";
}


std::string OsmParser::getType(const njson& feature)
{
    return feature["properties"]["type"];
}


long long OsmParser::getId(const njson& feature)
{
    return feature["properties"]["id"];
}


double OsmParser::getLat(const njson& feature)
{
    return feature["geometry"]["coordinates"][1];
}


double OsmParser::getLon(const njson& feature)
{
    return feature["geometry"]["coordinates"][0];
}





