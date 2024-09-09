#include "mapitems.h"


using namespace maykitbo::maps;


MapItem::MapItem(const SceneSet& set, const MapStyle& style,
                 const GeoJson::Feature& feature) :
    set_(set), style_(style), feature_(feature) {}


void MapItem::draw()
{
    feature_.geomWay([&] (point_s point)
    {
        polygon_.push_back(set_.adaptPoint(point));
    });
    path_.addPolygon(polygon_);
    setPath(path_);
    paint();
}


void PolygonItem::paint()
{
    if (feature_.isBuilding())
    {
        setBrush(feature_.isApartment() ? style_.apartments : style_.buildings);
    }
    else
    {
        // std::cout << feature_.propertiesToString() << "\n\n";
        setPen(style_.basic_polygon);
    }
}


void RoadItem::paint()
{
    setPen(style_.basic_road);
}


void LineItem::paint()
{
    setPen(style_.basic_line);
}
