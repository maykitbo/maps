#pragma once


#include <QGraphicsScene>
#include <QPolygon>
#include <QGraphicsLineItem>

#include "sceneset.h"
#include "geojson_handler.h"
#include "map_style.h"


namespace maykitbo::maps
{


class MapItem : public QGraphicsPathItem
{
    public:
        MapItem(const SceneSet& set, const MapStyle& style,
                const GeoJson::Feature& feature);
        virtual ~MapItem() = default;
        void draw();

    protected:
        const SceneSet& set_;
        const MapStyle style_;
        const GeoJson::Feature& feature_;
        QPolygonF polygon_;
        QPainterPath path_;
        virtual bool paint() = 0;
};


class PolygonItem : public MapItem
{
    using MapItem::MapItem;
    public:
        // PolygonItem()
        bool paint() override;
    private:
        bool findBrush(const MapStyle::brush_map& map,
                      const std::string& key);
};


// class PolygonItem : public QGraphicsPolygonItem
// {
//     // using MapItem::MapItem;
//     public:
//         PolygonItem();
        
//         // bool paint() override;
//     private:
//         // bool findBrush(const MapStyle::brush_map& map,
//         //               const std::string& key);
// };


class RoadItem : public MapItem
{
    using MapItem::MapItem;
    public:
        bool paint() override;
};


class LineItem : public MapItem
{
    using MapItem::MapItem;
    public:
        bool paint() override;
};


} // namespace maykitbo::maps

