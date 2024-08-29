#pragma once


#include <fstream>
#include <ranges>

#include "../../settings/config.h"
#include "../../settings/types.h"


namespace maykitbo::maps {


struct OsmParser {
    static json_t getJson(data_idx_t idx);

    static const json_t& getFeatures(const json_t& data);

    // reaturn vector of 4 floats: south, west, north, east
    // if idx is not exists return empty vector
    static std::vector<coord_t> getBbox(data_idx_t idx);

    static std::string getType(const json_t& feature);
    static feat_idx_t getId(const json_t& feature);
    static bool isNode(const json_t& feature);
    static bool isWay(const json_t& feature);

    // for nodes
    static coord_t getLat(const json_t& feature);
    static coord_t getLon(const json_t& feature);

    // for ways
    static const auto getNodes(const json_t& feature)
    {
        return feature["properties"]["nodes"] |
            std::views::transform([](const json_t& node) {
                return node.get<feat_idx_t>();
            });
    }
};


} // namespace maykitbo::maps
