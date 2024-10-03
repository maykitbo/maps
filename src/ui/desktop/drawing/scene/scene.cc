#include "scene.h"


using namespace maykitbo::maps;


#define _DRAW_FUNC_ drawMap


Scene::Scene(const IData& data, QObject* parent) :
    QGraphicsScene(parent),
    data_(data)
{
    // db_time_.pause();
    // draw_time_.pause();

    installEventFilter(parent);
}


void Scene::initMap()
{   
    set_.setBbox(style_.init_bbox);
    set_.setRect(style_.init_width);
    setSceneRect(0, 0, set_.width, set_.height);
    set_.setScale();

    // std::cout << set_;

    _DRAW_FUNC_();

}


void Scene::move(coord_t x, coord_t y)
{
    set_.move(x * style_.move_procent,
              y * style_.move_procent);
    _DRAW_FUNC_();
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
    _DRAW_FUNC_();
}


void Scene::scrollCloser()
{
    scroll(-1);
}


void Scene::scrollAway()
{
    scroll(1);
}


void Scene::adapt(QPolygonF& polygon)
{
    for (auto& point : polygon)
    {
        point = set_.adaptPoint(point);
    }
}

