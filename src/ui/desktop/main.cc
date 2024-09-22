#include "idata.h"
#include "config.h"
#include "mainwindow.h"


#include <QApplication>


int main(int argc, char *argv[])
{
    setenv("LC_NUMERIC", "C", 1);

    QApplication a(argc, argv);

    maykitbo::maps::IData db(maykitbo::maps::Conf::postgis);
    maykitbo::maps::MainWindow ui(db);

    ui.show();
    return a.exec();
}
