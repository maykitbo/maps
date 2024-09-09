#include "geojson_handler.h"


using namespace maykitbo::maps;


GeoJson::GeoJson(data_t&& data)
    : data_(data) {}


const GeoJson::data_t& GeoJson::getJsonData() const
{
    return data_;
}


void GeoJson::features(const std::function<void(const Feature&)>& func) const
{
    if (!data_.contains("features"))
    {
        std::cerr << "GeoJSON Error: json does not contains Features\n";
        return;
    }
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
    if (data_["geometry"]["coordinates"][0][0].is_array()) {
        for (const auto& line : data_["geometry"]["coordinates"])
        {
            for (const auto& point : line)
            {
                func(point_s{point[1], point[0]});
            }
        }
    }
    else
    {
        for (const auto& point : data_["geometry"]["coordinates"])
        {
            func(point_s{point[1], point[0]});
        }
    }
}


std::string GeoJson::Feature::toString() const {
    return data_.dump(2);
}


std::string GeoJson::Feature::propertiesToString() const
{
    return data_["properties"].dump(2);
}


const GeoJson::data_t& GeoJson::Feature::getJsonData() const
{
    return data_;
}


bool GeoJson::Feature::isBuilding() const
{
    return data_["properties"].contains("building");
}


bool GeoJson::Feature::isApartment() const
{
    return data_["properties"]["building"] == "apartments";
}





