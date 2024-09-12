#include "scene.h"


using namespace maykitbo::maps;


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

    // drawMap();
    drawMap2();

}


void Scene::move(int x, int y)
{
    set_.move((coord_t)x * style_.move_procent,
              (coord_t)y * style_.move_procent);
    drawMap2();
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
    move(0, 1);
}


void Scene::scrollCloser()
{

}


void Scene::scrollAway()
{

}


void Scene::drawMap2()
{
    clear();

    TimeTest overhead_time("overhead");

    QFuture<void> future_polygons = QtConcurrent::run([&]() {
        GeoJson polygons = data_.fetchPolygons(set_.bbox);
        QMetaObject::invokeMethod(this,
            [&, p = std::move(polygons)]() { drawItems<PolygonItem>(p); }, Qt::QueuedConnection);
    });

    // QFuture<void> future_roads = QtConcurrent::run([&]() {
    //     GeoJson roads = data_.fetchRoads(set_.bbox);
    //     QMetaObject::invokeMethod(this,
    //         [&, r = std::move(roads)]() { drawItems<RoadItem>(r); }, Qt::QueuedConnection);
    // });

    QFuture<void> future_lines = QtConcurrent::run([&]() {
        GeoJson lines = data_.fetchLines(set_.bbox);
        QMetaObject::invokeMethod(this,
            [&, l = std::move(lines)]() { drawItems<LineItem>(l); }, Qt::QueuedConnection);
    });

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
    TimeTest db_time("sum database");

    
    // Create futures for each fetch operation
    QFuture<GeoJson> future_polygons = QtConcurrent::run([&]()
    {
        return data_.fetchPolygons(set_.bbox);
    });

    QFuture<GeoJson> future_roads = QtConcurrent::run([&]()
    {
        return data_.fetchRoads(set_.bbox);
    });

    QFuture<GeoJson> future_lines = QtConcurrent::run([&]()
    {
        return data_.fetchLines(set_.bbox);
    });

    // Wait for all futures to finish
    future_polygons.waitForFinished();
    future_roads.waitForFinished();
    future_lines.waitForFinished();

    db_time.pause();
    TimeTest draw_time("sum draw");

    drawItems<PolygonItem>(future_polygons.result());
    drawItems<RoadItem>(future_roads.result());
    drawItems<LineItem>(future_lines.result());

    draw_time.pause();
    overhead_time.pause();

    std::cout << db_time << draw_time <<
                 overhead_time;
}