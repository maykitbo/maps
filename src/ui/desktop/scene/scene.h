#pragma once


#include <QGraphicsScene>

#include "idata.h"
#include "sceneset.h"
#include "mapitems.h"
#include "map_style.h"


namespace maykitbo::maps
{


class Scene : public QGraphicsScene
{
    Q_OBJECT

    public:
        Scene(const IData& data, QObject* parent = nullptr);
        // void setRect(int width, int height);
        void initMap();
        void drawMap();
        // void update(const bbox_s& bbox);

    
    protected:
        SceneSet set_;
        MapStyle style_;
        const IData& data_;

        template<class Item, class Func>
        void drawElement(Func fetch);

        void setRect(int width, int height);
};


template<class Item, class Func>
void Scene::drawElement(Func fetch)
{
    GeoJson osm = (data_.*fetch)(set_.bbox, 4326);
    osm.features([&] (const GeoJson::Feature& feature)
    {
        Item *item = new Item(set_, style_, feature);
        item->draw();
        addItem(item);
    });
}


} // namespace maykitbo::maps
