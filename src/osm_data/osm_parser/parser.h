#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <ranges>

#include "config.h"

struct OsmParser {
    using njson = nlohmann::json;
    static njson getJson(unsigned idx);

    // reaturn vector of 4 floats: south, west, north, east
    // if idx is not exists return empty vector
    static std::vector<double> getBbox(unsigned idx);

    static std::string getType(const njson& feature);
    static long long getId(const njson& feature);
    static bool isNode(const njson& feature);
    static bool isWay(const njson& feature);

    // for nodes
    static double getLat(const njson& feature);
    static double getLon(const njson& feature);

    // for ways
    static const auto getNodes(const njson& feature)
    {
        return feature["properties"]["nodes"] | std::views::transform([](const njson& node) {
            return node.get<long long>();
        });
    }
};
