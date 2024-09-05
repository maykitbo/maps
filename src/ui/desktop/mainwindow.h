#pragma once


#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>


#include "idata"
// #include "icore"


namespace maykitbo::maps
{


class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        void setCore(ICore* core);
        void setData(IData* data);

    private:
        IData* data_;
        // ICore* core_;

        QGraphicsView *view_;
        QGraphicsScene *scene_;
        void drawGraph(int idx);
};


} // namespace maykitbo::maps
