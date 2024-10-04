#pragma once


#include <types.h>
#include <cmath>
#include <algorithm>


namespace maykitbo::maps
{


// geographic coordinate system
struct GCS
{
    static constexpr const coord_t r_earth = 6371000; // Radius of the Earth in meters
    static constexpr const coord_t epsg_e = 20037508.34; // constant to convert epsg

    static coord_t ruler4326(point_s a, point_s b);
    static coord_t ruler3857(point_s a, point_s b);
    static coord_t toRadians(coord_t degree);
    static coord_t area3857(const bbox_s& bbox);
    static coord_t area4326(const bbox_s& bbox);

    static point_s epsg4326toEpsg3857(point_s p);
    static point_s epsg3857toEpsg4326(point_s p);
};


} // namespace maykitbo::maps