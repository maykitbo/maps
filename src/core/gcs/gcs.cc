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


coord_t GCS::area(const bbox_s& bbox)
{
    return ruler(point_s{bbox.max_lat, bbox.max_lon}, point_s{bbox.min_lat, bbox.max_lon}) *
           ruler(point_s{bbox.max_lat, bbox.max_lon}, point_s{bbox.min_lat, bbox.max_lon});
}



coord_t GCS::toRadians(coord_t degree)
{
    return degree * M_PI / 180.0;
}


point_s GCS::epsg4326toEpsg3857(point_s p)
{
    coord_t x = (p.lat * epsg_e) / 180.0;
    coord_t y = std::log(std::tan((90.0 + p.lon) * M_PI / 360.0)) / (M_PI / 180.0);
    y = (y * epsg_e) / 180.0;
    return {x, y};
}

point_s GCS::epsg3857toEpsg4326(point_s p)
{
    double x = (p.lat * 180.0) / epsg_e;
    double y = (p.lon * 180.0) / epsg_e;
    y = (std::atan(std::pow(M_E, y * (M_PI / 180.0))) * 360.0) / M_PI - 90.0;
    return {x, y};
}
