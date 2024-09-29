#pragma once


#include <QGraphicsScene>
#include <QPolygon>
#include <QGraphicsLineItem>
#include <QGraphicsSceneHoverEvent>
#include <QObject>
#include <QGraphicsSceneMouseEvent>

// #include "sceneset.h"
#include "map_style.h"
// #include "scene.h"


namespace maykitbo::maps
{


// class MetaItem
// {
//     public:
//         MetaItem()
// }


class PolygonItem : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT

    public:
        PolygonItem(const QPolygonF& polygon, idx_t id, const QBrush& brush, const IData& db) :
            QGraphicsPolygonItem(polygon),
            id_(id),
            basic_brush_(brush),
            highlight_brush_{brush.color().lighter(MapStyle::hover_highlight)},
            db_(db)
        {
            setBrush(basic_brush_);
            setAcceptHoverEvents(true);
        }
        idx_t idx() const { return id_; }

    // signals:
    //     void mousePressed();

    private:
        idx_t id_;
        QBrush basic_brush_;
        QBrush highlight_brush_;
        const IData& db_;

        void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override
        {
            setBrush(highlight_brush_);
        }

        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override
        {
            setBrush(basic_brush_);
        }

        void mousePressEvent(QGraphicsSceneMouseEvent *event) override
        {
            std::cout << "\n" << id_ << ": MOUSE PRESSED\n" << db_.polygonInfoAsString(id_) << "\n\n";
            // emit mousePressed();
        }

};


} // namespace maykitbo::maps

