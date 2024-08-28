#include "data/interface/data_manager.h"
#include "constroller/controller.h"
#include "ui/interface/iui.h"
#include "core/interface/icore.h"


#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    maykitbo::maps::ICore icore;
    maykitbo::maps::DataManager data_manager;
    maykitbo::maps::MainWindow ui;

    icore.setData(data);
    ui.setData(data);
    ui.setCore(core);

    ui.show();
    return a.exec();
}
