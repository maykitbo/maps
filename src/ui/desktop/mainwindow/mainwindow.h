#pragma once


#include <QMainWindow>
#include <QGraphicsView>
#include <QKeyEvent>

#include "scene.h"


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

        void connectKeyEvents();
        bool keyPress(QKeyEvent* key_event);
        void initScene();
    
    signals:
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
        void scrollCloser();
        void scrollAway();
    
    protected:
        bool eventFilter(QObject *object, QEvent *event);
    
};


} // namespace maykitbo::maps
