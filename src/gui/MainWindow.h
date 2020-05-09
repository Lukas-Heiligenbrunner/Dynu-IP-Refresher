//
// Created by lukas on 09.05.20.
//

#pragma once


#include <QtWidgets/QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow{
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
//    void startdownloadBtn();
void checkConfigBtn();
void refreshIPBtn();
signals:
    void appendLogField(QString);
//    void setInfoLabelText(QString);
//    void setProgressBarValue(int);
};