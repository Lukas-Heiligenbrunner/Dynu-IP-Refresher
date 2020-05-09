//
// Created by lukas on 09.05.20.
//

#include <iostream>
#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    ui->textLog->

//    ui->labelCurrentIP->setText("currently is nothing to do");
//    ui->labelConfig->setText("blabliblub");
//    ui->textfieldname->setText("hangover");

    connect(ui->buttonCheckConfig, SIGNAL(clicked()), this, SLOT(checkConfigBtn()));
    connect(ui->buttonRefreshIP, SIGNAL(clicked()), this, SLOT(refreshIPBtn()));

    connect(this, SIGNAL(appendLogField(QString)), ui->textLog, SLOT(appendPlainText(QString)));
//    connect(this, SIGNAL(setProgressBarValue(int)), ui->progressmanual, SLOT(setValue(int)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::checkConfigBtn() {
    std::cout << "btn clicked!" << std::endl;

    appendLogField("btn clicked! \n");
}

void MainWindow::refreshIPBtn() {

}