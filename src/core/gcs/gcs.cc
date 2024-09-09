#include "gcs.h"


using namespace maykitbo::maps;


coord_t GCS::ruler(point_s a, point_s b)
{
    // Convert latitudes and longitudes from degrees to radians
    coord_t lat1 = toRadians(a.lat);
    coord_t lon1 = toRadians(a.lon);
    coord_t lat2 = toRadians(b.lat);
    coord_t lon2 = toRadians(b.lon);

    coord_t sindlat = std::sin((lat2 - lat1) / 2);
    coord_t sindlon = std::sin((lon2 - lon1) / 2);

    coord_t haversine = sindlat * sindlat +
                       std::cos(lat1) *
                       std::cos(lat2) *
                       sindlon * sindlon;

    return 2.0 *
           std::atan2(std::sqrt(haversine),
                      std::sqrt(1 - haversine)) *
           r_earth;
}


coord_t GCS::toRadians(coord_t degree)
{
    return degree * M_PI / 180.0;
}
