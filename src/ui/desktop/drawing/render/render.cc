#include "render.h"
#include "scene.h"


using namespace maykitbo::maps;


Render::Render(const SceneSet& set, const MapStyle& style)
    :
        set_(set),
        style_(style),
        stop_(false)
{}

Render::~Render() {
    stop();
}

void Render::stop() {
    stop_ = true;
}

void Render::start() {
    stop_ = false;
}


void Render::drawPoints(const PointSet& set)
{
    if (stop_) return; // Check the stop flag before processing

    // std::cout << set.size() << " points\n";

    if (LoD::points(set_.real_area)) return;

    for (const auto& feature : set)
    {
        QPointF point = set_.adaptPoint(feature.coordinates()[0]);
        QRectF rect(point.x(), point.y(), style_.point_r, style_.point_r);
        idx_t id = feature.idx();

        emit pointItemReady(new PointItem(rect, id, style_.basic_point));
    }
}


void Render::drawRoads(const RoadSet& set)
{
    if (stop_) return; // Check the stop flag before processing

    // std::cout << set.size() << " roads\n";

    if (!LoD::points(set_.real_area)) return;

    for (const auto& feature : set)
    {
        auto type_iter = style_.lines.find(feature.type());
        if (type_iter != style_.lines.end())
        {
            auto way = feature.coordinates();
            QPolygonF polygon = set_.adapt(way);
            QPainterPath path;
            path.addPolygon(polygon);

            emit roadItemReady(new RoadItem(path, feature.idx(), type_iter->second));
        }
    }
}


void Render::drawPolygons(const PolygonSet& set)
{
    if (stop_) return; // Check the stop flag before processing

    std::cout << set.size() << " polygons\n";

    long long sum_size = 0;

    for (const auto& feature : set)
    {
        auto type_iter = style_.polygons.find(feature.type());
        if (type_iter != style_.polygons.end())
        {
            auto way = feature.coordinates();
            QPolygonF polygon = set_.adapt(way);

            sum_size += polygon.size();

            emit polygonItemReady(new PolygonItem(polygon, feature.idx(), type_iter->second));
        }
    }
}

void Render::drawLines(const LineSet& set)
{
    if (stop_) return; // Check the stop flag before processing

    // std::cout << set.size() << " lines\n";

    if (LoD::points(set_.real_area)) return;

    for (const auto& feature : set)
    {
        auto type_iter = style_.lines.find(feature.type());
        if (type_iter != style_.lines.end())
        {
            auto way = feature.coordinates();
            QPolygonF polygon = set_.adapt(way);
            QPainterPath path;
            path.addPolygon(polygon);

            emit lineItemReady(new LineItem(path, feature.idx(), type_iter->second));
        }
    }    
}

