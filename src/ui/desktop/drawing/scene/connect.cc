#include "scene.h"


using namespace maykitbo::maps;


void Scene::connectPolygonInfo(MapItem* item)
{
    connect(item, &PolygonItem::showInfo, [&, id = item->idx()] {
        std::cout << id << " INFO:\n" << data_.polygonInfoAsString(id) << '\n';
    });
}


void Scene::connectPointInfo(MapItem* item)
{
    connect(item, &PointItem::showInfo, [&, id = item->idx()] {
        std::cout << id << " POINTS INFO:\n" << data_.pointInfoAsString(id) << '\n';
    });
}


void Scene::connectLineInfo(MapItem* item)
{
    connect(item, &LineItem::showInfo, [&, id = item->idx()] {
        std::cout << id << " LINE INFO:\n" << data_.lineInfoAsString(id) << '\n';
    });
}


void Scene::connectRoadInfo(MapItem* item)
{
    connect(item, &LineItem::showInfo, [&, id = item->idx()] {
        std::cout << id << " ROAD INFO:\n" << data_.roadInfoAsString(id) << '\n';
    });
}



void Scene::connectRouteKey(MapItem* item)
{
    connect(item, &PolygonItem::mousePressed, [&, item] {
        if (route_start_ && route_end_)
        {
            unPress(&route_start_);
            if (route_start_ != item && route_end_ != item)
            {
                press(item, &route_start_);
            }
            unPress(&route_end_);
        }
        else if (!route_start_)
        {
            press(item, &route_start_);
        }
        else if (route_start_ == item)
        {
            unPress(&route_start_);
        }
        else
        {
            press(item, &route_end_);
            data_.route(route_start_->idx(), route_end_->idx());
            // std::cout << "route from " << route_start_->idx() << " to " << route_end_->idx() << '\n';
        }
    });
}


void Scene::press(MapItem* item, MapItem** point)
{
    *point = item;
    (*point)->press();
}


void Scene::unPress(MapItem** point)
{
    (*point)->unPress();
    *point = nullptr;
}


