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
        SceneSet set_;
        MapStyle style_;
        const IData& data_;

        void drawMap();
        void drawMap2();

        void move(int x, int y);

        template<class Item>
        void drawItems(const GeoJson& osm);

};


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
