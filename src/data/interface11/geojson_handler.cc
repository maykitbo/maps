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
    : data_(data), properties_(data_["properties"]) {}


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
    return properties_.dump(2);
}


const GeoJson::data_t& GeoJson::Feature::getJsonData() const
{
    return data_;
}


bool GeoJson::Feature::isBuilding() const
{
    return properties_.contains("building");
}


// bool GeoJson::Feature::isConstruction() const
// {
//     return properties_.contains("construction");
// }


std::string GeoJson::Feature::buildingType() const
{
    if (properties_.contains("disused") && properties_["disused"] == "yes")
    {
        return "disused";
    }

    std::string building_type = properties_["building"];
    if (building_type == "yes")
    {
        if (properties_.contains("construction"))
        {
            return "construction";
        }
        else if (properties_.contains("amenity"))
        {
            return properties_["amenity"];
        }
    }
    return building_type;
}


// bool GeoJson::Feature::isApartment() const
// {
//     return data_["properties"]["building"] == "apartments";
// }


bool GeoJson::Feature::isHighway() const
{
    return data_["properties"].contains("highway");
}


std::string GeoJson::Feature::highwayType() const
{
    return data_["properties"]["highway"];
}


bool GeoJson::Feature::isNatural() const
{
    return data_["properties"].contains("natural");
}


bool GeoJson::Feature::isLeisure() const
{
    return data_["properties"].contains("leisure");
}


bool GeoJson::Feature::isLanduse() const
{
    return data_["properties"].contains("landuse");
}


bool GeoJson::Feature::isAmenity() const
{
    return data_["properties"].contains("amenity");
}


bool GeoJson::Feature::isConstruction() const
{
    return data_["properties"].contains("construction");
}


bool GeoJson::Feature::isDisused() const
{
    return data_["properties"].contains("disused");
}


std::string GeoJson::Feature::laisureType() const
{
    return data_["properties"]["leisure"];
}


std::string GeoJson::Feature::naturalType() const
{
    return data_["properties"]["natural"];
}









