#include "mapitems.h"


using namespace maykitbo::maps;


MapItem::MapItem(const SceneSet& set, const MapStyle& style,
                 const GeoJson::Feature& feature) :
    set_(set), style_(style), feature_(feature) {}


void MapItem::draw()
{
    if (paint())
    {
        feature_.geomWay([&] (point_s point)
        {
            polygon_.push_back(set_.adaptPoint(point));
        });
        path_.addPolygon(polygon_);
        setPath(path_);
    }
}


bool PolygonItem::paint()
{
    if (feature_.isBuilding())
    {
        auto b_type = style_.buildings.find(feature_.buildingType());
        if (b_type != style_.buildings.end())
        {
            setBrush(b_type->second);
            return true;
        }
        else
        {
            std::cout << "NOT INT THE MAP " << feature_.propertiesToString() << "\n";
        }
    }
    else
    {
        if (feature_.isConstruction())
        {
            // setBrush(QBrush{QColor{255, 0, 0}});
            // std::cout << "CONSTRUCTION BUT NOT BUILDING in " << feature_.propertiesToString() << '\n';
            // return true;
        }
    }
    return false;
}


bool RoadItem::paint()
{
    setPen(style_.basic_road);
    return true;
}


bool LineItem::paint()
{
    if (feature_.isHighway())
    {
        auto hw_type = style_.roads.find(feature_.highwayType());
        if (hw_type != style_.roads.end())
        {
            setPen(hw_type->second);
            return true;
        }
        else
        {
            std::cout << "Unknown line.highway type: " <<
                         feature_.getJsonData()["properties"]["highway"] << '\n';
        }
    }
    else
    {
        // std::cout << "LINE IS NOT HIGHWAY " << feature_.propertiesToString() << '\n';
    }
    return false;
}
