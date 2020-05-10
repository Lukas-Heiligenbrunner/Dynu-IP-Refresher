#include <inc/api/IPAPI.h>
#include <inc/IPRefresher.h>
#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "inc/Config.h"
#include "inc/Logger.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // needs to be defined out of scope -- would be termintated after this constructor.
//    myThread = std::thread([this](){
//        IPAPI ipapi;
//        std::string ip = ipapi.getGlobalIp();
//        Logger::message("Current global IP: " + ip);
//        std::string msg = "Your current global IP: "+ip;
//        ui->labelCurrentIP->setText(msg.c_str());
//    });


    if (Config::validateConfig())
        ui->labelConfig->setText("Config is: OK");
    else
        ui->labelConfig->setText("Config is: NOT OK");

    connect(ui->buttonCheckConfig, SIGNAL(clicked()), this, SLOT(checkConfigBtn()));
    connect(ui->buttonRefreshIP, SIGNAL(clicked()), this, SLOT(refreshIPBtn()));

    connect(this, SIGNAL(appendLogField(QString)), ui->textLog, SLOT(appendPlainText(QString)));
//    connect(this, SIGNAL(setProgressBarValue(int)), ui->progressmanual, SLOT(setValue(int)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::checkConfigBtn() {
    Logger::message("checking config!");
    appendLogField("checking config!");

    if (Config::validateConfig()) {
        Logger::message("Config file is OK");
        appendLogField("Config file is OK");
        ui->labelConfig->setText("Config is: OK");
    } else {
        Logger::error("There are errors in config file!");
        appendLogField("There are errors in config file!");
    }
    appendLogField("");
}

void MainWindow::refreshIPBtn() {
    Logger::message("start refreshing Dynu IP.");
    appendLogField("");
    appendLogField("start refreshing Dynu IP.");
new std::thread([this](){
    IPRefresher ipr;
    if (Config::readConfig()) {
        ipr.checkIPAdress(false);
    } else {
        std::cout << "incorrect credentials!" << std::endl;
    }

    Logger::message("Finished refreshing Dynu IP.");
    appendLogField("Finished refreshing Dynu IP.");
    delete this;
});
//    myThread = std::thread([this](){
//        IPRefresher ipr;
//        if (Config::readConfig()) {
//            ipr.checkIPAdress(false);
//        } else {
//            std::cout << "incorrect credentials!" << std::endl;
//        }
//
//        Logger::message("Finished refreshing Dynu IP.");
//        appendLogField("Finished refreshing Dynu IP.");
//        ui->textLog->appendPlainText("Finished refreshing Dynu IP.");
//    });


}