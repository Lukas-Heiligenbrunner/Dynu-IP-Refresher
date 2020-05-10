//
// Created by lukas on 09.05.20.
//

#include <QApplication>
#include <iostream>
#include "gui/MainWindow.h"

int main(int argc, char *argv[]) {
    std::cout << "gui here!" << std::endl;
    QCoreApplication::addLibraryPath(".");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return QApplication::exec();
}