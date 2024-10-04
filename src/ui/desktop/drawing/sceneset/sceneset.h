#pragma once


#include <QPointF>
#include <functional>
#include <QPolygonF>

#include "types.h"
#include "gcs.h"
#include "idata/idata.h"


namespace maykitbo::maps
{


struct SceneSet
{
    static constexpr const coord_t max_poly_bbox = 2e8;
    static const int bbox_sep_depth = 0;

    coord_t width;
    coord_t height;
    coord_t real_width;
    coord_t real_height;
    coord_t real_area;
    bbox_s bbox;
    coord_t lon_scale;
    coord_t lat_scale;
    coord_t delta_lat;
    coord_t delta_lon;

    QPointF adaptPoint(point_s point) const;
    QPointF adaptPoint(QPointF point) const;
    QPointF adaptPoint(coord_t lat, coord_t lon) const;
    void adapt(QPolygonF& polygon) const;
    QPolygonF adapt(const IData::coordinates_t& way) const;

    void setScale();
    void setRect(int width);
    void setBbox(const bbox_s& bbox);
    void move(coord_t x, coord_t y);
    void scroll(coord_t v);
    std::pair<bbox_s, bbox_s> halfBbox();
    void setDelta();
    void calcReals();

    void bboxSeparation(std::function<void(const bbox_s&)> func) const;
    void bboxSeparation(int depth, const bbox_s& bbox, std::function<void(const bbox_s&)> func) const;


    friend std::ostream& operator<<(std::ostream& os, const SceneSet& ss)
    {
        os << "width = " << ss.width << '\n';
        os << "height = " << ss.height << '\n';
        os << "delta lat = " << ss.delta_lat << '\n';
        os << "delta lon = " << ss.delta_lon << '\n';
        os << ss.bbox;
        os << "lat scale = " << ss.lat_scale << '\n';
        os << "lon scale = " << ss.lon_scale << '\n';
        std::cout << "real width = " << ss.real_width << " meters\n";
        std::cout << "real height = " << ss.real_height << " meters\n";
        return os;
    }

    // signals:

};


} // namespace maykitbo::maps

