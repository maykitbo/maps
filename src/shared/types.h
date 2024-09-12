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
 * @typedef nodeid_t
 * Integer type for representing node IDs.
 */
typedef long long unsigned nodeid_t;

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

/**
 * @struct bbox_s
 * Represents a bounding box (rectangular area) on a map.
 */
struct bbox_s {
    coord_t max_lat;
    coord_t min_lat;
    coord_t max_lon;
    coord_t min_lon;

    friend std::ostream &operator<<(std::ostream& os, const bbox_s& b)
    {
        os << "max_lat = " << b.max_lat << '\n';
        os << "min_lat = " << b.min_lat << '\n';
        os << "max_lon = " << b.max_lon << '\n';
        os << "min_lon = " << b.min_lon << '\n';
        return os;
    }
    bbox_s(coord_t top, coord_t buttom, coord_t right, coord_t left)
        : max_lat(top), min_lat(buttom), max_lon(right), min_lon(left) {}
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
    std::vector<nodeid_t> node_ids;

    /**
     * List of way IDs that connect the nodes in the route.
     */
    std::vector<nodeid_t> way_ids;
};


} // namespace maykitbo::maps
