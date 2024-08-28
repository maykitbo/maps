#pragma once


#include "idata"
#include "icore"
#include "mainwindow.h"


namespace maykitbo::maps
{


class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        IData* data_;
        ICore* core_;

        QGraphicsView *view_;
        QGraphicsScene *scene_;
        void drawGraph(int idx);
};


} // namespace maykitbo::maps