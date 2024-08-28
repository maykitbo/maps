#include "algebra.h"


using namespace maykitbo::maps;


coord_t Algebra::toRadians(coord_t degree)
{
    return degree * M_PI / 180.0;
}


rlen_t Algebra::distanse(coord_t lat1, coord_t lon1, coord_t lat2, coord_t lon2)
{
    // Convert latitude from degrees to radians
    lat1 = toRadians(lat1);
    lat2 = toRadians(lat2);

    // Haversine formula
    rlen_t sindlat = std::sin((lat2 - lat1) / 2.0);
    rlen_t sindlon = std::sin((toRadians(lon2) - toRadians(lon1)) / 2.0);

    rlen_t a = sindlat * sindlat +
               std::cos(lat1) * std::cos(lat2) *
               sindlon * sindlon;

    return 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a)) * Constants::r_earth;
}


