#pragma once


#include <QPointF>

#include "types.h"
#include "gcs.h"


namespace maykitbo::maps
{


struct SceneSet
{
    coord_t width;
    coord_t height;
    coord_t real_width;
    coord_t real_height;
    bbox_s bbox;
    coord_t lon_scale;
    coord_t lat_scale;
    coord_t delta_lat;
    coord_t delta_lon;
    QPointF adaptPoint(point_s point) const;
    void setScale();
    void setRect(int width);
    void setBbox(const bbox_s& bbox);
    void move(coord_t x, coord_t y);
    std::pair<bbox_s, bbox_s> halfBbox();

    friend std::ostream& operator<<(std::ostream& os, const SceneSet& ss)
    {
        os << "width = " << ss.width << '\n';
        os << "height = " << ss.height << '\n';
        os << "delta lat = " << ss.delta_lat << '\n';
        os << "delta lon = " << ss.delta_lon << '\n';
        os << ss.bbox;
        os << "lat scale = " << ss.lat_scale << '\n';
        os << "lon scale = " << ss.lon_scale << '\n';
        std::cout << "real width on the top = " <<
                      GCS::ruler(point_s{ss.bbox.max_lat, ss.bbox.min_lon},
                                 point_s{ss.bbox.max_lat, ss.bbox.max_lon}) <<
                      " meters\n";
        std::cout << "real width on the buttom = " <<
                      GCS::ruler(point_s{ss.bbox.min_lat, ss.bbox.min_lon},
                                 point_s{ss.bbox.min_lat, ss.bbox.max_lon}) <<
                      " meters\n";
        std::cout << "real width = " << ss.real_width << " meters\n";
        std::cout << "real height = " << ss.real_height << " meters\n";
        return os;
    }
};


} // namespace maykitbo::maps

