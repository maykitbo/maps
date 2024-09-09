#include "scene.h"


using namespace maykitbo::maps;


Scene::Scene(const IData& data, QObject* parent) :
    QGraphicsScene(parent),
    data_(data)
{

}


void Scene::initMap()
{   
    set_.setBbox(style_.init_bbox);
    set_.setRect(style_.init_width);
    setSceneRect(0, 0, set_.width, set_.height);
    set_.setScale();

    // std::cout << set_;

    drawMap();
}


void Scene::drawMap()
{
    drawElement<PolygonItem>(&IData::fetchPolygons);
    drawElement<RoadItem>(&IData::fetchRoads);
    drawElement<LineItem>(&IData::fetchLines);
}