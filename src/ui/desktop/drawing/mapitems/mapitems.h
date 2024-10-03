#pragma once


#include <QGraphicsScene>
#include <QPolygon>
#include <QGraphicsLineItem>
#include <QGraphicsSceneHoverEvent>
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>


// #include "sceneset.h"
#include "map_style.h"
#include "idata.h"
// #include "scene.h"


namespace maykitbo::maps
{


class MapItem : public QObject
{
    Q_OBJECT

    public:
        MapItem(idx_t id);
        idx_t idx() const;
        virtual void highlight() = 0;
        virtual void undoHighlight() = 0;
        void unPress();
        void press();
        bool pressed() const;

    signals:
        void mousePressed();
        void showInfo();

    protected:
        idx_t id_;
        bool pressed_;

        void hoverEnter(QGraphicsSceneHoverEvent *event);
        void hoverLeave(QGraphicsSceneHoverEvent *event);
        void mousePress(QGraphicsSceneMouseEvent *event);
};


class BrushMapItem : public MapItem
{
    public:
        BrushMapItem(idx_t id, const QBrush& brush);

    protected:
        QBrush basic_brush_;
        QBrush highlight_brush_;
};


class PenMapItem : public MapItem
{
    public:
        PenMapItem(idx_t id, const QPen& pen);
    
    protected:
        QPen basic_pen_;
        QPen highlight_pen_;
};


class LineItem : public PenMapItem, public QGraphicsPathItem
{
    public:
        LineItem(const QPainterPath& polygon, idx_t id, const QPen& pen);

        void highlight() override;
        void undoHighlight() override;
    
    protected:
        QPainterPath shape() const override {
            QPainterPathStroker stroker;
            stroker.setWidth(2.0); // Adjust the width as needed
            return stroker.createStroke(path());
        }

        void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override
            { hoverEnter(event); }
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override
            { hoverLeave(event); }
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override
            { mousePress(event); }
};


class PolygonItem : public BrushMapItem, public QGraphicsPolygonItem
{
    public:
        PolygonItem(const QPolygonF& polygon, idx_t id, const QBrush& brush);

        void highlight() override;
        void undoHighlight() override;
    
    private:
        void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override
            { hoverEnter(event); }
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override
            { hoverLeave(event); }
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override
            { mousePress(event); }
};


class PointItem : public BrushMapItem, public QGraphicsEllipseItem
{
    public:
        PointItem(const QRectF& rect, idx_t id, const QBrush& brush);

        void highlight() override;
        void undoHighlight() override;
    
    private:
        void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override
            { hoverEnter(event); }
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override
            { hoverLeave(event); }
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override
            { mousePress(event); }
};


} // namespace maykitbo::maps

