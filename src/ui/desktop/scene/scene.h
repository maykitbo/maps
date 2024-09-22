#pragma once


#include <QGraphicsScene>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QMetaObject>
#include <QGraphicsPolygonItem>
// #include <QGraphicsLineItem>

#include "idata/idata.h"
#include "sceneset.h"
#include "map_style.h"
#include "lod.h"

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
        friend class QPointFPreprocess;
        SceneSet set_;
        MapStyle style_;

        const IData& data_;

        using PolygonSet = decltype(
            data_.fethPolygons<QPolygonF, QPointFPreprocess>(
                bbox_s{}, d_area_s{}, 0));
        
        using LineSet = decltype(
            data_.fethLines<QPolygonF, QPointFPreprocess>(
                bbox_s{}, 0, 0));

        void drawMap();
        // void drawMap2();

        void move(coord_t x, coord_t y);
        void scroll(coord_t v);

        void drawPolygons(const PolygonSet& set);
        void drawLines(const LineSet& set);

        void adapt(QPolygonF& polygon)
        {
            for (auto& point : polygon)
            {
                point = set_.adaptPoint(point);
            }
        }

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
