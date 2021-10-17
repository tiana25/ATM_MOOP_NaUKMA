#include "mainwindow.h"

#include <QApplication>
#include "SessionManager.h"
#include <QDir>
#include <QDebug>
#include <QStandardPaths>


int main(int argc, char *argv[]) {


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
