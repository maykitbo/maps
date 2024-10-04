#pragma once


#include <QObject>
#include <QMetaObject>

#include <functional>
#include <atomic>

#include "idata/idata.h"
#include "mapitems.h"
#include "sceneset.h"
#include "map_style.h"


namespace maykitbo::maps
{


class Render : public QObject
{
    Q_OBJECT

    public:
        Render(const SceneSet& set, const MapStyle& style);

        ~Render();

        void stop();
        void start();

    signals:
        void polygonItemReady(PolygonItem* set);
        void lineItemReady(LineItem* set);
        void roadItemReady(RoadItem* set);
        void pointItemReady(PointItem* set);

    public slots:
        void drawPolygons(const PolygonSet& set);
        void drawLines(const LineSet& set);
        void drawPoints(const PointSet& set);
        void drawRoads(const RoadSet& set);

    private:
        const SceneSet& set_;
        const MapStyle& style_;
        std::atomic<bool> stop_;


};





} // namespace maykitbo::maps

