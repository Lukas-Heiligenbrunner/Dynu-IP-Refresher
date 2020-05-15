#include <QApplication>
#include "gui/MainWindow.h"

/**
 * application entry point
 */
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("startUpService");
    w.show();

    return QApplication::exec();
}