#include "scene.h"


using namespace maykitbo::maps;


void Scene::drawMap()
{
    clear();

    std::cout << "Real AREA = " << set_.real_area << "\n";
    std::cout << "BBOX = {" << set_.bbox << "}\n";

    TimeTest overhead_time("overhead");
    TimeTest db_time("data requests");

    TimeTest poly_db_time("polygon data request");
    QFuture<PolygonSet> future_polygons = QtConcurrent::run([&]()
    {
        PolygonSet R = data_.fetchPolygons<QPolygonF, QPointFPreprocess>(
            set_.bbox, LoD::maxMinArea(set_.real_area), LoD::sparse(set_.real_area));

        poly_db_time.pause();

        return R;
    });

    TimeTest line_db_time("line data request");
    QFuture<LineSet> future_lines = QtConcurrent::run([&]()
    {
        if (LoD::points(set_.real_area))
        {
            line_db_time.pause();
            return LineSet{};
        }

        LineSet R = data_.fetchLines<QPolygonF, QPointFPreprocess>(
            set_.bbox, LoD::minLineDrawType(set_.real_area));

        line_db_time.pause();

        return R;
    });

    TimeTest read_db_time("road data request");
    QFuture<RoadSet> future_roads = QtConcurrent::run([&]()
    {
        if (!LoD::points(set_.real_area))
        {
            read_db_time.pause();
            return RoadSet{};
        }

        RoadSet R = data_.fetchRoads<QPolygonF, QPointFPreprocess>(
            set_.bbox, LoD::minLineDrawType(set_.real_area));

        read_db_time.pause();

        return R;
    });

    TimeTest point_db_time("point data request");
    QFuture<PointSet> future_points = QtConcurrent::run([&]()
    {
        if (LoD::points(set_.real_area))
        {
            point_db_time.pause();
            return PointSet{};
        }
        
        PointSet R = data_.fetchPoints<std::vector<QPointF>, QPointFPreprocess>(set_.bbox);

        point_db_time.pause();

        return R;
    });

    future_polygons.waitForFinished();
    future_lines.waitForFinished();
    future_roads.waitForFinished();
    future_points.waitForFinished();

    db_time.pause();

    TimeTest draw_time("draw");

    drawPolygons(future_polygons.result());
    drawLines(future_lines.result());
    drawPoints(future_points.result());
    drawRoads(future_roads.result());

    overhead_time.pause();
    draw_time.pause();

    std::cout <<
                poly_db_time <<
                line_db_time <<
                point_db_time <<
                read_db_time <<
                db_time <<
                draw_time <<
                overhead_time;
}


void Scene::drawPoints(const PointSet& set)
{
    std::cout << set.size() << " points\n";

    if (LoD::points(set_.real_area)) return;

    for (const auto& feature : set)
    {
        QPointF point = set_.adaptPoint(feature.coordinates()[0]);
        QRectF rect(point.x(), point.y(), style_.point_r, style_.point_r);
        idx_t id = feature.idx();

        PointItem* item = new PointItem(rect, id, style_.basic_point);

        connectPointInfo(item);
        connectRouteKey(item);

        addItem(item);
    }
}


void Scene::drawRoads(const RoadSet& set)
{
    std::cout << set.size() << " roads\n";

    if (!LoD::points(set_.real_area)) return;

    for (const auto& feature : set)
    {
        auto type_iter = style_.lines.find(feature.type());
        if (type_iter != style_.lines.end())
        {
            QPolygonF polygon = feature.coordinates();
            adapt(polygon);
            QPainterPath path;
            path.addPolygon(polygon);

            LineItem* item = new LineItem(path, feature.idx(), type_iter->second);

            connectRoadInfo(item);

            addItem(item);
        }

        // QPolygonF polygon = feature.coordinates();
        // adapt(polygon);
        // QPainterPath path;
        // path.addPolygon(polygon);
        // QGraphicsPathItem* item = new QGraphicsPathItem(path);
        // item->setPen(style_.basic_road);
        // addItem(item);
    }
}


void Scene::drawPolygons(const PolygonSet& set)
{
    std::cout << set.size() << " polygons\n";

    long long sum_size = 0;

    for (const auto& feature : set)
    {
        auto type_iter = style_.polygons.find(feature.type());
        if (type_iter != style_.polygons.end())
        {
            QPolygonF polygon = feature.coordinates();
            adapt(polygon);

            sum_size += polygon.size();

            PolygonItem* item = new PolygonItem(polygon, feature.idx(), type_iter->second);

            connectPolygonInfo(item);
            connectRouteKey(item);
            
            addItem(item);
        }
    }

    if (set.size())
        std::cout << "Mean polygon size = " <<          sum_size / set.size() << "\n" <<
                     "Sum of points in polygon = " <<   sum_size << "\n";
}

void Scene::drawLines(const LineSet& set)
{
    std::cout << set.size() << " lines\n";

    if (LoD::points(set_.real_area)) return;

    for (const auto& feature : set)
    {
        auto type_iter = style_.lines.find(feature.type());
        if (type_iter != style_.lines.end())
        {
            QPolygonF polygon = feature.coordinates();
            adapt(polygon);
            QPainterPath path;
            path.addPolygon(polygon);

            LineItem* item = new LineItem(path, feature.idx(), type_iter->second);

            connectLineInfo(item);

            addItem(item);
        }
    }    
}


