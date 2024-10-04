#pragma once


#include "sceneset.h"
#include "idata/idata.h"
#include "lod.h"


#include <QObject>
#include <QThread>

#include <memory>


namespace maykitbo::maps
{


class DataLoader : public QObject
{
    Q_OBJECT

    public:
        DataLoader(const SceneSet& set, IData& data);

    signals:
        void polygonDataReady(const PolygonSet& set);
        void lineDataReady(const LineSet& set);
        void roadDataReady(const RoadSet& set);
        void pointDataReady(const PointSet& set);
    
    public slots:
        void allTypes();

    private:
        using thread_t = std::unique_ptr<QThread>;

        const SceneSet &set_;
        IData& data_;

        void sepThreads();
        void oneThread();

        thread_t threadBuilder(const std::function<void(void)>& get);

        thread_t getPolygons();
        thread_t getLines();
        thread_t getPoints();
        thread_t getRoads();

    


};



} // namespace myakitbo::maps
