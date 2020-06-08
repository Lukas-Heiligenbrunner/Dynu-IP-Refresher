/**
 * Main GUI controller - User IO handlings
 *
 * @author Lukas Heiligenbrunner
 * @date 09.05.2020
 */

#pragma once

#include <QtWidgets/QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    /**
     * constructor with basic initializations
     */
    explicit MainWindow();

    /**
     * destruct all gui elements
     */
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    /**
     * all static initializations of custom gui elements
     */
    void initGui();

private slots:

    /**
     * executed click handler for config button
     */
    void checkConfigBtn();

    /**
     * executed click handler for refresh btn
     */
    void refreshIPBtn();

    /**
     * executed click handler for save config btn
     */
    void saveConfigBtn();

signals:

    /**
     * append a String line to the Log field
     *
     * @param QString string to be appended
     */
    void appendLogField(QString);
};