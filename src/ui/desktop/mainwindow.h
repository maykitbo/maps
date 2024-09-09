#pragma once


#include <QMainWindow>
#include <QGraphicsView>

#include "scene/scene.h"


namespace maykitbo::maps
{


class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(const IData& data, QWidget *parent = nullptr);

    private:
        const IData& data_;

        QGraphicsView *view_;
        Scene *scene_;
    
    // signals:

};


} // namespace maykitbo::maps
