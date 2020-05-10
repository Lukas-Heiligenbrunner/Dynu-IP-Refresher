//
// Created by lukas on 09.05.20.
//

#pragma once

#include <thread>
#include <QtWidgets/QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::thread myThread;
private slots:
//    void startdownloadBtn();
void checkConfigBtn();
void refreshIPBtn();
signals:
    void appendLogField(QString);
//    void setInfoLabelText(QString);
//    void setProgressBarValue(int);
};