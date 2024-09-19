#pragma once


#include <QGraphicsScene>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>
#include <QMetaObject>

#include "idata.h"
#include "sceneset.h"
#include "mapitems.h"
#include "map_style.h"
#include "lod.h"
#include "draw_polygon_data.h"

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
        friend class QPointFPreprocess;
        inline static SceneSet set_;
        inline static MapStyle style_;

        const IData& data_;

        void drawMap();
        void drawMap2();

        void move(coord_t x, coord_t y);
        void scroll(coord_t v);

        template<class Item>
        void drawItems(const GeoJson& osm);

        template<class Item, class Func>
        QFuture<void> fetchDraw(const Func &func);

};


struct QPointFPreprocess
{
    static QPointF act(double lat, double lon)
    {
        return Scene::set_.adaptPoint(lat, lon);
    }
};


template<class Item, class Func>
QFuture<void> Scene::fetchDraw(const Func &func)
{
    return QtConcurrent::run([&]() {
        GeoJson polygons = func();
        QMetaObject::invokeMethod(this,
            [&, p = std::move(polygons)]()
            {
                drawItems<Item>(p);
            },
            Qt::QueuedConnection);
    });
}


template<class Item>
void Scene::drawItems(const GeoJson& osm)
{
    osm.features([&](const GeoJson::Feature& feature) {
        Item* item = new Item(set_, style_, feature);
        item->draw();
        addItem(item);
    });
}


} // namespace maykitbo::maps
