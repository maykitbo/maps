#pragma once


#include <types.h>
#include <cmath>
#include <algorithm>


namespace maykitbo::maps
{


// geographic coordinate system
struct GCS
{
    static constexpr const coord_t r_earth = 6371000;// Radius of the Earth in meters
    static coord_t ruler(point_s a, point_s b);
    static coord_t toRadians(coord_t degree);
};


} // namespace maykitbo::maps