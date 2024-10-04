#pragma once


#include <QGraphicsScene>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QMetaObject>
#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>

#include <unordered_set>
#include <set>

#include "idata/idata.h"
#include "sceneset.h"
#include "map_style.h"
#include "lod.h"
#include "mapitems.h"
#include "render.h"
#include "dataloader.h"

#include "time_test.h"


namespace maykitbo::maps
{


class Scene : public QGraphicsScene
{
    Q_OBJECT

    public:
        Scene(IData& data, QObject* parent = nullptr);

        // SceneSet& set() { return set_; }
        // MapStyle& style() { return style_; }

    public slots:
        void initMap();
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
        void scrollCloser();
        void scrollAway();

        void addPolygonItem(PolygonItem* item);
        void addLineItem(LineItem* item);
        void addRoadItem(RoadItem* item);
        void addPointItem(PointItem* item);
    
    signals:
        void draw();

    protected:
        SceneSet set_;
        MapStyle style_;

        MapItem* route_start_{nullptr};
        MapItem* route_end_{nullptr};

        Render render_;
        DataLoader data_loader_;

        IData& data_;


        void move(coord_t x, coord_t y);
        void scroll(coord_t v);

        void connectRenderLoader();
        void connectSceneLoader();
        void connectRenderScene();

        void connectRouteKey(MapItem* item);

        void connectPolygonInfo(MapItem* item);
        void connectLineInfo(MapItem* item);
        void connectPointInfo(MapItem* item);
        void connectRoadInfo(MapItem* item);

        void press(MapItem* item, MapItem** point);
        void unPress(MapItem** point);
};



// struct Scene::QPointFPreprocess
// {
//     static QPointF act(double lat, double lon)
//     {
//         // return Scene::set_.adaptPoint(lat, lon);
//         return QPointF{lon, lat};
//     }
// };


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
