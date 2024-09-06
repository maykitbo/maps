#include "mainwindow.h"


using namespace maykitbo::maps;


MainWindow::MainWindow(IData& data, QWidget* parent) :
    QMainWindow(parent),
    data_(data)
{
    view_ = new QGraphicsView(this);
    scene_ = new QGraphicsScene(this);
    view_->setScene(scene_);
    setCentralWidget(view_);

    drawMap(bbox_s{37.8, 56.00, 38.00, 55.8});
}


void MainWindow::drawMap(const bbox_s& bbox)
{
    GeoJson osm = data_.fetchPolygons(bbox);
    osm.features([&] (const GeoJson::Feature& feature) {
        feature.geomWay([&] (point_s p) {
            std::cout << p.lat << '\t' << p.lon << '\n';
        });
    });
}

