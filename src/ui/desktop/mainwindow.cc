#include "mainwindow.h"


using namespace maykitbo::maps;


MainWindow::MainWindow(const IData& data, QWidget* parent) :
    QMainWindow(parent),
    data_(data),
    view_(new QGraphicsView(this)),
    scene_(new Scene(data_, this))
{
    view_->setScene(scene_);
    setCentralWidget(view_);

    scene_->initMap();

    setGeometry(10, 10, scene_->width() * 1.05, scene_->height() * 1.05);
}
    // bboxes = [
    // #   south    west    north   east
    //     (55.810, 37.660, 55.812, 37.666),
    //     (55.809, 37.655, 55.813, 37.666),
    //     (55.809, 37.650, 55.814, 37.666),
    //     (55.805, 37.650, 55.814, 37.666),
    //     (55.800, 37.645, 55.812, 37.666)
    // ]

