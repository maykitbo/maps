#include "mapitems.h"


using namespace maykitbo::maps;


MapItem::MapItem(idx_t id)
    :
        id_(id),
        pressed_(false)
{}


BrushMapItem::BrushMapItem(idx_t id, const QBrush& brush)
    :
        MapItem(id),
        basic_brush_(brush),
        highlight_brush_{brush.color().lighter(MapStyle::hover_highlight)}
{}


PenMapItem::PenMapItem(idx_t id, const QPen& pen)
    :
        MapItem(id),
        basic_pen_(pen),
        highlight_pen_(pen)
{
    highlight_pen_.setColor(pen.color().lighter(MapStyle::hover_highlight));
}



PolygonItem::PolygonItem(const QPolygonF& polygon, idx_t id, const QBrush& brush)
    :
        BrushMapItem(id, brush),
        QGraphicsPolygonItem(polygon)
{
    setAcceptHoverEvents(true);
    setBrush(basic_brush_);
}


PointItem::PointItem(const QRectF& rect, idx_t id, const QBrush& brush)
    :
        BrushMapItem(id, brush),
        QGraphicsEllipseItem(rect)
{
    setAcceptHoverEvents(true);
    setBrush(basic_brush_);
}


LineItem::LineItem(const QPainterPath& path, idx_t id, const QPen& pen)
    :
        PenMapItem(id, pen),
        QGraphicsPathItem(path)
{
    setAcceptHoverEvents(true);
    setPen(basic_pen_);
}


idx_t MapItem::idx() const
{
    return id_;
}


void MapItem::hoverEnter(QGraphicsSceneHoverEvent *event)
{
    highlight();
}


void MapItem::hoverLeave(QGraphicsSceneHoverEvent *event)
{
    if (!pressed_)
        undoHighlight();
}


void MapItem::mousePress(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() == Qt::ControlModifier)
        emit showInfo();
    else
        emit mousePressed();
}


bool MapItem::pressed() const
{
    return pressed_;
}


void MapItem::unPress()
{
    pressed_ = false;
    undoHighlight();
}

void MapItem::press()
{
    pressed_ = true;
    highlight();
}


void PointItem::highlight()
{
    setBrush(highlight_brush_);
}


void PointItem::undoHighlight()
{
    setBrush(basic_brush_);
}


void PolygonItem::highlight()
{
    setBrush(highlight_brush_);
}


void PolygonItem::undoHighlight()
{
    setBrush(basic_brush_);
}


void LineItem::highlight()
{
    setPen(highlight_pen_);
}


void LineItem::undoHighlight()
{
    setPen(basic_pen_);
}

