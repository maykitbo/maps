#include "scene.h"


using namespace maykitbo::maps;

Scene::Scene(IData& data, QObject* parent) :
    QGraphicsScene(parent),
    data_(data),
    render_(set_, style_),
    data_loader_(set_, data)
{
    installEventFilter(parent);

    connectRenderLoader();
    connectRenderScene();
    connectSceneLoader();
}


void Scene::initMap()
{   
    set_.setBbox(style_.init_bbox);
    set_.setRect(style_.init_width);
    setSceneRect(0, 0, set_.width, set_.height);
    set_.setScale();

    // std::cout << set_;

    emit draw();
}


void Scene::move(coord_t x, coord_t y)
{
    set_.move(x * style_.move_procent,
              y * style_.move_procent);

    clear();
    emit draw();
}


void Scene::moveLeft()
{
    move(-1, 0);
}


void Scene::moveRight()
{
    move(1, 0);
}


void Scene::moveUp()
{
    move(0, 1);
}


void Scene::moveDown()
{
    move(0, -1);
}


void Scene::scroll(coord_t v)
{
    set_.scroll(v * style_.scroll_procent);
    
    clear();
    emit draw();
}


void Scene::scrollCloser()
{
    scroll(-1);
}


void Scene::scrollAway()
{
    scroll(1);
}


void Scene::addPolygonItem(PolygonItem* item)
{
    connectPolygonInfo(item);
    connectRouteKey(item);
    addItem(item);
}


void Scene::addLineItem(LineItem* item)
{
    connectLineInfo(item);
    addItem(item);
}


void Scene::addRoadItem(RoadItem* item)
{
    connectRoadInfo(item);
    addItem(item);
}


void Scene::addPointItem(PointItem* item)
{
    connectPointInfo(item);
    connectRouteKey(item);
    addItem(item);
}

