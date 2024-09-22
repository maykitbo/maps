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


void Scene::drawMap()
{
    clear();

    std::cout << set_.real_area << '\n';

    TimeTest overhead_time("overhead");
    TimeTest db_time("data requests");

    TimeTest poly_db_time("polygon data request");
    QFuture<PolygonSet> future_polygons = QtConcurrent::run([&]()
    {
        auto R = data_.fethPolygons<QPolygonF, QPointFPreprocess>(
            set_.bbox, LoD::maxMinArea(set_.real_area));
        poly_db_time.pause();
        return R;
        // return data_.fethPolygons<QPolygonF, QPointFPreprocess>(
        //     set_.bbox, LoD::maxMinArea(set_.real_area));
    });

    TimeTest line_db_time("line data request");
    QFuture<LineSet> future_lines = QtConcurrent::run([&]()
    {
        auto R = data_.fethLines<QPolygonF, QPointFPreprocess>(
            set_.bbox, LoD::minLineDrawType(set_.real_area));
        line_db_time.pause();
        return R;
        // return data_.fethLines<QPolygonF, QPointFPreprocess>(
        //     set_.bbox, LoD::minLineDrawType(set_.real_area));
    });

    future_polygons.waitForFinished();
    future_lines.waitForFinished();

    db_time.pause();

    TimeTest draw_time("draw");

    drawPolygons(future_polygons.result());
    drawLines(future_lines.result());

    overhead_time.pause();
    draw_time.pause();

    std::cout <<
                 poly_db_time <<
                 line_db_time <<
                 db_time <<
                 draw_time <<
                 overhead_time;
}

void Scene::drawPolygons(const PolygonSet& set)
{
    std::cout << set.size() << " polygons\n";
    for (const auto& feature : set)
    {
        auto type_iter = style_.polygons.find(feature.type());
        if (type_iter != style_.polygons.end())
        {
            QPolygonF polygon = feature.coordinates();
            adapt(polygon);
            QGraphicsPolygonItem* item = new QGraphicsPolygonItem(polygon);
            item->setBrush(type_iter->second);
            addItem(item);
        }
        // else
        // {
        //     std::cout << "unknow polygon. Draw type = " << feature.type() << "\n";
        // }
    }    
}

void Scene::drawLines(const LineSet& set)
{
    std::cout << set.size() << " lines\n";
    for (const auto& feature : set)
    {
        auto type_iter = style_.lines.find(feature.type());
        if (type_iter != style_.lines.end())
        {
            QPolygonF polygon = feature.coordinates();
            adapt(polygon);
            QPainterPath path;
            path.addPolygon(polygon);
            QGraphicsPathItem* item = new QGraphicsPathItem(path);
            item->setPen(type_iter->second);
            addItem(item);
        }
        // else
        // {
        //     std::cout << "unknow line. Draw type = " << feature.type() << "\n";
        // }
    }    
}
