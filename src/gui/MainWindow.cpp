#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "api/IPAPI.h"
#include "IPRefresher.h"
#include "Config.h"
#include "Logger.h"

#include <thread>

MainWindow::MainWindow() : QMainWindow(), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // needs to be defined with new -- would be termintated after this constructor.
    new std::thread([this]() {
        IPAPI ipapi;
        std::string ip = ipapi.getGlobalIp();
        Logger::message("Current global IP: " + ip);
        std::string msg = "Your current global IP: " + ip;
        this->ui->labelCurrentIP->setText(msg.c_str());
    });

    // set config info label and initial check if config is valid
    ui->labelConfig->setText(Config::validateConfig() ? "Config is: OK" : "Config is: NOT OK");

    connect(ui->buttonCheckConfig, SIGNAL(clicked()), this, SLOT(checkConfigBtn()));
    connect(ui->buttonRefreshIP, SIGNAL(clicked()), this, SLOT(refreshIPBtn()));

    connect(this, SIGNAL(appendLogField(QString)), ui->textLog, SLOT(appendPlainText(QString)));
}

MainWindow::~MainWindow() {
    // todo check if disconnects are really necessary
    disconnect(ui->buttonCheckConfig);
    disconnect(ui->buttonRefreshIP);
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
    new std::thread([this]() {
        if (Config::readConfig()) {
            int code = IPRefresher::checkIPAdress(false);
            switch (code) {
                case IPRefresher::Status_Code::SUCCESS:
                    appendLogField("successfully refreshed IP!");
                    break;
                case IPRefresher::Status_Code::NOREFRESH:
                    appendLogField("IP is already correct.");
                    break;
                case IPRefresher::Status_Code::ERROR_NO_INTERNET:
                    appendLogField("Error: No Internet connection");
                    break;
                case IPRefresher::Status_Code::ERROR:
                    appendLogField("An error occured while refreshing.");
                    break;
                default:
                    appendLogField("An unknown error code occured");
            }
        } else {
            std::cout << "incorrect credentials!" << std::endl;
        }

        Logger::message("Finished refreshing Dynu IP.");
        this->appendLogField("Finished refreshing Dynu IP.");
    });
}