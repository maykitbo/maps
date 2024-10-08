#pragma once


#include <vector>
#include <iostream>


namespace maykitbo::maps
{

/**
 * @typedef coord_t
 * Floating-point type for coordinates (latitude and longitude).
 */
typedef double coord_t;

// /**
//  * @typedef distance_t
//  * Floating-point type for representing route lengths.
//  */
// typedef long long int distance_t;

/**
 * @typedef idx_t
 * Integer type for representing node IDs.
 */
typedef long long int idx_t;

/**
 * @struct point_s
 * Represents a point on a map with latitude and longitude coordinates.
 */
struct point_s {
    /**
     * Latitude coordinate of the point.
     */
    coord_t lat;

    /**
     * Longitude coordinate of the point.
     */
    coord_t lon;

    /**
     * Constructs a point on the map with the given latitude and longitude.
     *
     * @param lat Latitude coordinate.
     * @param lon Longitude coordinate.
     */
    point_s(coord_t lat, coord_t lon)
        : lat(lat), lon(lon) {}
};


struct d_area_s
{
    coord_t min;
    coord_t max;
    d_area_s(coord_t min, coord_t max) : min(min), max(max) {}
    d_area_s() = default;
};

/**
 * @struct bbox_s
 * Represents a bounding box (rectangular area) on a map.
 */
struct bbox_s {
    coord_t max_lat;
    coord_t min_lat;
    coord_t max_lon;
    coord_t min_lon;

    point_s topRight()
    {
        return {max_lat, max_lon};
    }
    point_s buttomLeft()
    {
        return {min_lat, min_lon};
    }

    void operator=(const bbox_s& other)
    {
        max_lat = other.max_lat;
        min_lat = other.min_lat;
        max_lon = other.max_lon;
        min_lon = other.min_lon;
    }

    friend std::ostream &operator<<(std::ostream& os, const bbox_s& b)
    {
        os << b.max_lat << ", " << b.min_lat << ", " << b.max_lon << ", " << b.min_lon;
        return os;
    }

    bbox_s(coord_t top, coord_t buttom, coord_t right, coord_t left)
        : max_lat(top), min_lat(buttom), max_lon(right), min_lon(left) {}

    bbox_s(point_s top_right, point_s buttom_left)
        : max_lat(top_right.lat), min_lat(buttom_left.lat),
          max_lon(top_right.lon), min_lon(buttom_left.lon) {}

    bbox_s() = default;
};

/**
 * @struct route_s
 * Represents a route on a map, including its length and the nodes and ways that define it.
 */
struct route_s {
    /**
     * Total length of the route.
     */
    // distance_t len;
    coord_t len;

    /**
     * List of node IDs that define the route.
     */
    std::vector<idx_t> node_ids;

    /**
     * List of way IDs that connect the nodes in the route.
     */
    std::vector<idx_t> way_ids;
};


} // namespace maykitbo::maps
