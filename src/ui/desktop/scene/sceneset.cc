#include "sceneset.h"


using namespace maykitbo::maps;


void SceneSet::setScale()
{
    lon_scale = width / delta_lon;
    lat_scale = height / delta_lat;
}


QPointF SceneSet::adaptPoint(point_s point) const
{
    return QPointF(
        (point.lon - bbox.min_lon) * lon_scale,
        height - (point.lat - bbox.min_lat) * lat_scale
    );
}


void SceneSet::setRect(int w)
{
    width = w;
    height = w * real_height / real_width;
}


void SceneSet::setBbox(const bbox_s& bb)
{
    bbox = bb;
    delta_lat = bbox.max_lat - bbox.min_lat;
    delta_lon = bbox.max_lon - bbox.min_lon;
    real_width = GCS::ruler(point_s{bbox.max_lat, bbox.min_lon},
                            point_s{bbox.max_lat, bbox.max_lon});
    real_height = GCS::ruler(point_s{bbox.min_lat, bbox.min_lon},
                             point_s{bbox.max_lat, bbox.min_lon});
}
