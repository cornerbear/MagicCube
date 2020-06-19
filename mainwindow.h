#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cube.h"
#include "turncubewidget.h"
#include <QTimer>
#include <debugmode.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    CubeData * cubedata;
    Cube * cube;
    TurnCubeWidget * turncubewidget;
    bool flag;
    QTimer* timer;

    static int second;
    static int minute;
    static int hour;

    DebugMode* debugMode;

    void mainInit();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
