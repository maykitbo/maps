#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include "osm_parser/parser.h"
#include <QPolygon>

#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    view_ = new QGraphicsView(this);
    scene_ = new QGraphicsScene(this);
    view_->setScene(scene_);
    setCentralWidget(view_);

    drawGraph(4);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::drawGraph(int idx)
{
    std::cout << "start drawing\n";

    std::vector<double> bbox = OsmParser::getBbox(idx);
    if (bbox.size() == 0)
    {
        qWarning("Incorrect index of json file");
        return;
    }
    nlohmann::json data = OsmParser::getJson(idx);

    // Define the scene size
    const int scene_width = 800;
    const int scene_height = 600;
    scene_->setSceneRect(0, 0, scene_width, scene_height);

    // Define the min and max latitude and longitude values
    double min_lon = bbox[1];
    double max_lon = bbox[3];
    double min_lat = bbox[0];
    double max_lat = bbox[2];

    // Calculate scaling factors
    double lon_scale = scene_width / (max_lon - min_lon);
    double lat_scale = scene_height / (max_lat - min_lat);

    std::map<long long, QPointF> nodes;

    for (const auto &feature : OsmParser::getFeatures(data))
    {
        if (OsmParser::isNode(feature))
        {
            long long id = OsmParser::getId(feature);
            double lat = OsmParser::getLat(feature);
            double lon = OsmParser::getLon(feature);

            // Transform coordinates to scene coordinates
            double x = (lon - min_lon) * lon_scale;
            double y = scene_height - (lat - min_lat) * lat_scale; // Invert y-axis

            nodes[id] = QPointF(x, y);
            scene_->addEllipse(x, y, 2, 2, QPen(), QBrush(Qt::SolidPattern));
        }
        else if (OsmParser::isWay(feature))
        {
            QPolygonF polygon;
            for (long long node_id : OsmParser::getNodes(feature))
            {
                auto point = nodes.find(node_id);
                if (point != nodes.end())
                {
                    polygon.push_back(point->second);
                }
                else
                {
                    qWarning("No such node in way");
                }

                QPainterPath path;
                path.addPolygon(polygon);

                QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);

                pathItem->setPen(QPen(Qt::green));
                auto brush_color = polygon.first() == polygon.last() ? Qt::blue : Qt::transparent;
                pathItem->setBrush(QBrush(brush_color));

                scene_->addItem(pathItem);
            }
        }
        else
        {
            qWarning("Unknown feature type");
        }
    }
}


