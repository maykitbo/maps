#pragma once


#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>


#include "idata.h"


namespace maykitbo::maps
{


class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(IData& data, QWidget *parent = nullptr);
        // ~MainWindow();

    private:
        IData& data_;

        QGraphicsView *view_;
        QGraphicsScene *scene_;
        void drawMap(const bbox_s& bbox);
};


} // namespace maykitbo::maps
