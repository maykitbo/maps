#include "sceneset.h"


using namespace maykitbo::maps;


void SceneSet::setScale()
{
    lon_scale = width / delta_lon;
    lat_scale = height / delta_lat;
}


QPointF SceneSet::adaptPoint(point_s point) const
{
    return QPointF
    {
        (point.lon - bbox.min_lon) * lon_scale,
        height - (point.lat - bbox.min_lat) * lat_scale
    };
}


QPointF SceneSet::adaptPoint(coord_t lat, coord_t lon) const
{
    return QPointF
    {
        (lon - bbox.min_lon) * lon_scale,
        height - (lat - bbox.min_lat) * lat_scale
    };
}



void SceneSet::setRect(int w)
{
    width = w;
    height = w * real_height / real_width;
}


void SceneSet::setDelta()
{
    delta_lat = bbox.max_lat - bbox.min_lat;
    delta_lon = bbox.max_lon - bbox.min_lon;
}


void SceneSet::calcReals()
{
    real_width = GCS::ruler(point_s{bbox.max_lat, bbox.min_lon},
                            point_s{bbox.max_lat, bbox.max_lon});
    real_height = GCS::ruler(point_s{bbox.min_lat, bbox.min_lon},
                             point_s{bbox.max_lat, bbox.min_lon});
    real_area = real_height * real_width;
}


void SceneSet::setBbox(const bbox_s& bb)
{
    bbox = bb;
    setDelta();
    calcReals();
}


void SceneSet::move(coord_t x, coord_t y)
{
    bbox.max_lat += delta_lat * y;
    bbox.min_lat += delta_lat * y;
    bbox.max_lon += delta_lon * x;
    bbox.min_lon += delta_lon * x;
}


void SceneSet::scroll(coord_t v)
{
    bbox.max_lat += delta_lat * v;
    bbox.min_lat -= delta_lat * v;
    bbox.max_lon += delta_lon * v;
    bbox.min_lon -= delta_lon * v;
    setDelta();
    calcReals();
    setScale();
}


std::pair<bbox_s, bbox_s> SceneSet::halfBbox()
{
    return std::pair<bbox_s, bbox_s>
    {
        bbox_s
        {
            bbox.max_lat - delta_lat / 2,
            bbox.min_lat,
            bbox.max_lon,
            bbox.min_lon
        },
        bbox_s
        {
            bbox.max_lat,
            bbox.min_lat + delta_lat / 2,
            bbox.max_lon,
            bbox.min_lon
        }
    };
}
