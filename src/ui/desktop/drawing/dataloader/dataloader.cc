#include "dataloader.h"


using namespace maykitbo::maps;


DataLoader::DataLoader(const SceneSet& set, IData& data)
    :
        set_(set),
        data_(data)
{}


void DataLoader::allTypes()
{
    // TimeTest overhead("DataLoader::allTypes overhead", true);
    std::cout << "Real area = " << set_.real_area << "\n";

    std::vector<thread_t> threads;
    threads.push_back(getPolygons());
    threads.push_back(getLines());
    threads.push_back(getRoads());
    threads.push_back(getPoints());

    for (const auto& T : threads)
        T->start();
    
    for (const auto& T : threads)
        T->wait();
}


DataLoader::thread_t DataLoader::threadBuilder(const std::function<void(void)>& get)
{
    thread_t thread = std::make_unique<QThread>();

    connect(thread.get(), &QThread::started, [get, thd = thread.get()]
    {
        get();
        thd->quit();
    });

    return thread;
}


std::unique_ptr<QThread> DataLoader::getPolygons()
{
    return threadBuilder([&]
    {
        TimeTest poly_db_time("polygon data request", true);

        set_.bboxSeparation([&] (const bbox_s& bb) {
            PolygonSet R = data_.fetchPolygons(
                bb, LoD::maxMinArea(set_.real_area), LoD::sparse(set_.real_area));

            emit polygonDataReady(R);
        });
    });
}


std::unique_ptr<QThread> DataLoader::getLines()
{
    return threadBuilder([&]
    {
        // TimeTest line_db_time("line data request", true);

        if (LoD::points(set_.real_area))
            return;

        LineSet R = data_.fetchLines(
            set_.bbox, LoD::minLineDrawType(set_.real_area));

        emit lineDataReady(R);
    });
}


std::unique_ptr<QThread> DataLoader::getPoints()
{
    return threadBuilder([&]
    {
        // TimeTest point_db_time("point data request", true);

        if (LoD::points(set_.real_area))
            return;
        
        PointSet R = data_.fetchPoints(set_.bbox);

        emit pointDataReady(R);
    });

}


std::unique_ptr<QThread> DataLoader::getRoads()
{
    return threadBuilder([&]
    {
        // TimeTest read_db_time("road data request", true);

        if (!LoD::points(set_.real_area))
            return;

        RoadSet R = data_.fetchRoads(
            set_.bbox, LoD::minLineDrawType(set_.real_area));

        emit roadDataReady(R);
    });
}




