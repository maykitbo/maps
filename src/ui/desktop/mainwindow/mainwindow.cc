#include "mainwindow.h"


using namespace maykitbo::maps;


MainWindow::MainWindow(const IData& data, QWidget* parent) :
    QMainWindow(parent),
    data_(data),
    view_(new QGraphicsView(this)),
    scene_(new Scene(data_, this))
{
    initScene();
    setGeometry(10, 10, scene_->width() * 1.05, scene_->height() * 1.05);
    // setGeometry(10, 10, 1000, 1000 * 1.05);
}


void MainWindow::initScene()
{
    view_->setScene(scene_);
    setCentralWidget(view_);
    
    scene_->installEventFilter(this);
    view_->installEventFilter(this);
    // setFocusPolicy(Qt::StrongFocus); 

    connectKeyEvents();

    scene_->initMap();
}


bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* key_event = dynamic_cast<QKeyEvent*>(event);
        return keyPress(key_event);
    }
    return false; 
}


bool MainWindow::keyPress(QKeyEvent* key_event)
{
    switch (key_event->key())
    {
        case Qt::Key_Left:
            std::cout << "Left pressed\n";
            emit moveLeft();
            return true;

        case Qt::Key_Right:
            std::cout << "Right pressed\n";
            emit moveRight();
            return true;

        case Qt::Key_Up:
            std::cout << "Up pressed\n";
            emit moveUp();
            return true;

        case Qt::Key_Down:
            std::cout << "Down pressed\n";
            emit moveDown();
            return true;
        
        case Qt::Key_Plus:
        case Qt::Key_Equal:
            std::cout << "Plus pressed\n";
            emit scrollCloser();
            return true;
        
        case Qt::Key_Minus:
            std::cout << "Minus pressed\n";
            emit scrollAway();
            return true;
    }
    return false;
}


void MainWindow::connectKeyEvents()
{
    connect(this,   &MainWindow::moveLeft,
            scene_, &Scene::moveLeft);

    connect(this,   &MainWindow::moveRight,
            scene_, &Scene::moveRight);

    connect(this,   &MainWindow::moveUp,
            scene_, &Scene::moveUp);

    connect(this,   &MainWindow::moveDown,
            scene_, &Scene::moveDown);
    
    connect(this,   &MainWindow::scrollAway,
        scene_, &Scene::scrollAway);
    
    connect(this,   &MainWindow::scrollCloser,
        scene_, &Scene::scrollCloser);
}


// void MainWindow::keyPressEvent(QKeyEvent* e)
// {
//     std::cout << "Key pressed\n";
//     switch (e->key()) {
//         case Qt::Key_Left:
//             std::cout << "Left pressed\n";
//             emit moveLeft();
//             break;
//         case Qt::Key_Right:
//             std::cout << "Right pressed\n";
//             emit moveRight();
//             break;
//         case Qt::Key_Up:
//             std::cout << "Up pressed\n";
//             emit moveUp();
//             break;
//         case Qt::Key_Down:
//             std::cout << "Down pressed\n";
//             emit moveDown();
//             break;
//         default:
//             QMainWindow::keyPressEvent(e);  // Pass the event to the base class for default handling
//     }
// }

