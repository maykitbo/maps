#pragma once


#include <vector>


namespace maykitbo::maps
{

/**
 * @typedef coord_t
 * Floating-point type for coordinates (latitude and longitude).
 */
typedef double coord_t;

/**
 * @typedef distance_t
 * Floating-point type for representing route lengths.
 */
typedef double distance_t;

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
    /**
     * Top-left corner of the bounding box.
     */
    point_s left_top;

    /**
     * Bottom-right corner of the bounding box.
     */
    point_s right_buttom;

    /**
     * Constructs a bounding box with the given coordinates.
     *
     * @param left   Longitude of the left edge.
     * @param top    Latitude of the top edge.
     * @param right  Longitude of the right edge.
     * @param buttom Latitude of the bottom edge.
     */
    bbox_s(coord_t left, coord_t top, coord_t right, coord_t buttom)
        : left_top(top, left), right_buttom(buttom, right) {}

    /**
     * Constructs a bounding box with the given top-left and bottom-right points.
     *
     * @param left_top      Top-left corner of the bounding box.
     * @param right_buttom  Bottom-right corner of the bounding box.
     */
    bbox_s(const point_s& left_top, const point_s& right_buttom)
        : left_top(left_top), right_buttom(right_buttom) {}
};

/**
 * @struct route_s
 * Represents a route on a map, including its length and the nodes and ways that define it.
 */
struct route_s {
    /**
     * Total length of the route.
     */
    distance_t len;

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
