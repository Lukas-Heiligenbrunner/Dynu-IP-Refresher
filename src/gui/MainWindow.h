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
private slots:
    /**
     * executed click handler for config button
     */
    void checkConfigBtn();

    /**
     * executed click handler for refresh btn
     */
    void refreshIPBtn();

signals:
    /**
     * append a String line to the Log field
     *
     * @param QString string to be appended
     */
    void appendLogField(QString);
};