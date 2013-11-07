/*
 *Submitted by Donald Villareal & Joseph Wagner & Kevin Sekniqi(?)
 */
#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWin;
    mainWin.resize(800,600);
    mainWin.showMaximized();
    return app.exec();
}
