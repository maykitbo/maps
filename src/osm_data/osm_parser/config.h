#pragma once

#include <string>

struct OsmConfig {
    inline static std::string data_path = "/home/alexey/projects/maps/osm_data/";

    inline const static std::string data_type = ".geo.json";
    inline const static std::string data_prefix = "osm_";
    inline const static std::string description = "description.txt";

    static std::string getDataPath(int idx) {
        return data_path + data_prefix + std::to_string(idx) + data_type;
    }
    static std::string getDescriptionPath() {
        return data_path + description;
    }

};


