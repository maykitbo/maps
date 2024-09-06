#include "geojson_handler.h"


using namespace maykitbo::maps;


GeoJson::GeoJson(data_t&& data)
    : data_(data) {}


void GeoJson::features(const std::function<void(const Feature&)>& func) const
{
    for (const auto& feature : data_["features"])
        func(Feature(feature));
}

std::string GeoJson::toString() const {
    return data_.dump(2);
}


GeoJson::Feature::Feature(const data_t& data)
    : data_(data) {}


void GeoJson::Feature::geomWay(const std::function<void(point_s)>& func) const
{
    for (const auto& point : data_["geometry"]["coordinates"])
        func(point_s{point[1], point[0]});
}


std::string GeoJson::Feature::toString() const {
    return data_.dump(2);
}


