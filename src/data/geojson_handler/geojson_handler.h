#pragma once


#include <nlohmann/json.hpp>
#include <functional>
#include <unordered_map>
#include <iostream>

#include "types.h"


namespace maykitbo::maps
{


// enum GeomType
// {
//     LineString
// };


// struct GetGeomType
// {
//     private:
//         inline const static std::unordered_map<std::string, GeomType> gt_ =
//             {
//                 {"LineString", GeomType::LineString}
//             };
//     public:
//         static GeomType operator()(const std::string& s)
//             { return GetGeomType::gt_[s]; }
// };


/**
 * Represents a GeoJSON object, providing methods to interact with its features.
 *
 * The `GeoJson` class encapsulates a GeoJSON object and provides methods to
 * iterate over its features and convert the entire object to a string.
 * It uses the `nlohmann::json` library for JSON manipulation.
 */
class GeoJson {
public:
    using data_t = nlohmann::json;

    /**
     * Represents a feature within a GeoJSON object.
     *
     * The `Feature` class encapsulates a single feature within a GeoJSON object.
     * It provides methods to interact with the feature's geometry and properties.
     */
    class Feature;

    /**
     * Constructs a `GeoJson` object from a JSON data object.
     *
     * @param data A JSON object representing the GeoJSON data.
     *             The data is moved into the `GeoJson` object to avoid unnecessary copies.
     */
    GeoJson(data_t&& data);

    /**
     * Iterates over all features in the GeoJSON object.
     *
     * This method accepts a callback function that is called for each feature
     * in the GeoJSON object. The callback function receives a `Feature` object
     * representing the current feature.
     *
     * @param func A callback function that takes a `const Feature&` as its parameter.
     */
    void features(const std::function<void(const Feature&)>& func) const;

    /**
     * Converts the GeoJSON object to a string.
     *
     * This method returns a string representation of the entire GeoJSON object.
     * The string is formatted with 2 spaces of indentation for readability.
     *
     * @return A string representation of the GeoJSON object.
     */
    std::string toString() const;

    const data_t& getJsonData() const;

private:
    data_t data_;
};

/**
 * Represents a feature within a GeoJSON object.
 *
 * The `Feature` class encapsulates a single feature within a GeoJSON object.
 * It provides methods to interact with the feature's geometry and properties.
 */
class GeoJson::Feature {
public:
    using data_t = nlohmann::json;

    /**
     * Constructs a `Feature` object from a JSON data object.
     *
     * @param data A JSON object representing the feature data.
     *             The data is referenced by the `Feature` object, so it must
     *             remain valid for the lifetime of the `Feature`.
     */
    Feature(const data_t& data);

    /**
     * Iterates over all points in the feature's geometry.
     *
     * This method accepts a callback function that is called for each point
     * in the feature's geometry. The callback function receives a `point_s`
     * object representing the current point.
     *
     * @param func A callback function that takes a `point_s` as its parameter.
     */
    void geomWay(const std::function<void(point_s)>& func) const;

    /**
     * Converts the feature to a string.
     *
     * This method returns a string representation of the feature.
     * The string is formatted with 2 spaces of indentation for readability.
     *
     * @return A string representation of the feature.
     */
    std::string toString() const;

    std::string propertiesToString() const;

    const data_t& getJsonData() const;
    // bool isConstruction() const;
    bool isHighway() const;
    std::string highwayType() const;

    // polygon
    bool isBuilding() const;
    std::string buildingType() const;
    bool isNatural() const;
    bool isLeisure() const;
    bool isLanduse() const;
    bool isAmenity() const;
    bool isConstruction() const;
    bool isDisused() const;
    std::string laisureType() const;
    std::string naturalType() const;

private:
    const data_t& data_;
    const data_t& properties_;
};



} // namespace maykitbo::maps

