#pragma once


#include <QGraphicsScene>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QMetaObject>
#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>

#include <unordered_set>
// #include <QGraphicsLineItem>

#include "idata/idata.h"
#include "sceneset.h"
#include "map_style.h"
#include "lod.h"
#include "mapitems.h"

#include "time_test.h"


namespace maykitbo::maps
{


class Scene : public QGraphicsScene
{
    Q_OBJECT

    public:
        Scene(const IData& data, QObject* parent = nullptr);

    public slots:
        void initMap();
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
        void scrollCloser();
        void scrollAway();
        
    
    protected:
        class QPointFPreprocess;

        SceneSet set_;
        MapStyle style_;
        MapItem* route_start_{nullptr};
        MapItem* route_end_{nullptr};

        const IData& data_;

        using PolygonSet = decltype(
            data_.fetchPolygons<QPolygonF, QPointFPreprocess>(
                bbox_s{}, d_area_s{}, 0));
        
        using LineSet = decltype(
            data_.fetchLines<QPolygonF, QPointFPreprocess>(
                bbox_s{}, 0, 0));

        using RoadSet = decltype(
            data_.fetchRoads<QPolygonF, QPointFPreprocess>(
                bbox_s{}, 0, 0));

        using PointSet = decltype(
            data_.fetchPoints<std::vector<QPointF>, QPointFPreprocess>(
                bbox_s{}, 0));

        void drawMap();

        void move(coord_t x, coord_t y);
        void scroll(coord_t v);

        void adapt(QPolygonF& polygon);

        void drawPolygons(const PolygonSet& set);
        void drawLines(const LineSet& set);
        void drawPoints(const PointSet& set);
        void drawRoads(const RoadSet& set);

        void connectRouteKey(MapItem* item);
        void connectPolygonInfo(MapItem* item);
        void connectLineInfo(MapItem* item);
        void connectPointInfo(MapItem* item);
        void connectRoadInfo(MapItem* item);
        void press(MapItem* item, MapItem** point);
        void unPress(MapItem** point);

        // void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
        // bool sceneEventFilter(QGraphicsItem *watched, QEvent *event) override;
        // bool eventFilter(QObject *watched, QEvent *event) override;
};



struct Scene::QPointFPreprocess
{
    static QPointF act(double lat, double lon)
    {
        // return Scene::set_.adaptPoint(lat, lon);
        return QPointF{lon, lat};
    }
};


// template<class Item, class Func>
// QFuture<void> Scene::fetchDraw(const Func &func)
// {
//     return QtConcurrent::run([&]() {
//         GeoJson polygons = func();
//         QMetaObject::invokeMethod(this,
//             [&, p = std::move(polygons)]()
//             {
//                 drawItems<Item>(p);
//             },
//             Qt::QueuedConnection);
//     });
// }


// template<class Item>
// void Scene::drawItems(const GeoJson& osm)
// {
//     osm.features([&](const GeoJson::Feature& feature) {
//         Item* item = new Item(set_, style_, feature);
//         item->draw();
//         addItem(item);
//     });
// }


} // namespace maykitbo::maps
