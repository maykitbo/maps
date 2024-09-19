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


bool PolygonItem::findBrush(const MapStyle::brush_map& map,
                            const std::string& key)
{
    auto brush = map.find(key);
    if (brush != map.end())
    {
        setBrush(brush->second);
        return true;
    }
    else
    {
        std::cout << "NOT INT THE MAP " << feature_.propertiesToString() << "\n";
    }
    return false;
}


bool PolygonItem::paint()
{
    // if (feature_.isBuilding())
    // {
    //     return findBrush(style_.buildings, feature_.buildingType());
    // }
    // else if (feature_.isConstruction())
    // {
    //     setBrush(style_.areas.find("construction")->second);
    //     return true;
    // }
    // else if (feature_.isDisused())
    // {
    //     setBrush(style_.areas.find("disused")->second);
    //     return true;
    // }
    // else if (feature_.isLeisure())
    // {
    //     return findBrush(style_.areas, feature_.laisureType());
    // }
    // else if (feature_.isNatural())
    // {
    //     return findBrush(style_.areas, feature_.naturalType());
    // }
    // else
    // {
    //     // std::cout << feature_.propertiesToString() << '\n';
    // }
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
                         feature_.propertiesToString() << '\n';
        }
    }
    else
    {
        // std::cout << "LINE IS NOT HIGHWAY " << feature_.propertiesToString() << '\n';
    }
    return false;
}
