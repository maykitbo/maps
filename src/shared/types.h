#pragma once


#include <vector>


namespace maykitbo::maps
{


// float pointing type for coordinates
typedef double coord_t;

// float pointing type for route length
typedef double distance_t;

// integer type for nodes id
typedef long long unsigned nodeid_t;

// struct for point on a map
struct point_s
{
    coord_t lat;
    coord_t lon;
    point_s(coord_t lat, coord_t lon)
        : lat(lat), lon(lon) {}
};

// struct for bbox. Rect on a map
struct bbox_s
{
    point_s left_top;
    point_s right_buttom;
    bbox_s(coord_t left, coord_t top, coord_t right, coord_t buttom)
        : left_top(top, left), right_buttom(buttom, right) {}
    bbox_s(const point_s& left_top, const point_s& right_buttom)
        : left_top(left_top), right_buttom(right_buttom) {}
};

// storage type for route
struct route_s
{
    // route distance
    distance_t len;
    // nodes to connect the route
    std::vector<nodeid_t> node_ids;
    // ways to connect the nodes
    std::vector<nodeid_t> way_ids;
};


} // namespace maykitbo::maps
