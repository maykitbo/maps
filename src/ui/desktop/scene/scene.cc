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


void Scene::drawMap2()
{
    clear();

    TimeTest overhead_time("overhead");

    QFuture<void> future_polygons = fetchDraw<PolygonItem>([&]
        {
            return data_.fetchPolygons(set_.bbox,
                                       LoD::maxMinArea(set_.real_area));
        }
    );

    // QFuture<void> future_roads = fetchDraw<RoadItem>([&]
    //     {
    //         return data_.fetchRoads(set_.bbox);
    //     }
    // );

    QFuture<void> future_lines = fetchDraw<LineItem>([&]
        {
            return data_.fetchLines(set_.bbox);
        }
    );

    // Wait for all futures to finish
    future_polygons.waitForFinished();
    // future_roads.waitForFinished();
    future_lines.waitForFinished();

    overhead_time.pause();

    std::cout << overhead_time;
}


void Scene::drawMap()
{
    clear();

    TimeTest overhead_time("overhead");
    // TimeTest db_time("sum database");

    // std::cout << "REAL AREA = " << set_.real_area << '\n';
    
    QFuture<DrawPolygonData<QPolygonF, QPointFPreprocess>> future_polygons = QtConcurrent::run([&]()
    {
        // return data_.fetchPolygons(set_.bbox,
        //                            LoD::maxMinArea(set_.real_area));
        DrawPolygonData<QPolygonF, QPointFPreprocess> data;
        data.fetch(set_.bbox, LoD::maxMinArea(set_.real_area));
        return data;
    });

    // QFuture<GeoJson> future_roads = QtConcurrent::run([&]()
    // {
    //     return data_.fetchRoads(set_.bbox);
    // });

    QFuture<GeoJson> future_lines = QtConcurrent::run([&]()
    {
        return data_.fetchLines(set_.bbox);
    });

    // Wait for all futures to finish
    future_polygons.waitForFinished();
    // future_roads.waitForFinished();
    future_lines.waitForFinished();

    // db_time.pause();
    // TimeTest draw_time("sum draw");

    // drawItems<PolygonItem>(future_polygons.result());
    
    future_polygons.result().forEach(
        [&] (const DrawPolygonData<QPolygonF, QPointFPreprocess>::Feature& feature)
    {
        auto type_iter = style_.polygons.find(feature.type());
        if (type_iter != style_.polygons.end())
        {
            const QPolygonF& polygon = feature.coordinates();
            QGraphicsPolygonItem* item = new QGraphicsPolygonItem(polygon);
            item->setBrush(type_iter->second);
            addItem(item);
        }
    });

    // drawItems<RoadItem>(future_roads.result());
    drawItems<LineItem>(future_lines.result());

    // draw_time.pause();
    overhead_time.pause();

    std::cout <<
                // db_time << draw_time <<
                 overhead_time;
}