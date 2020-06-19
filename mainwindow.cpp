#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "cube.h"
#include "threeordercube.h"
#include "fourordercube.h"
#include <QMessageBox>
#include "cubedata.h"
#include <QTimer>
#include "turncubewidget.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowIcon(QPixmap(":/res/cube.png"));
    cubedata = NULL;
    debugMode = NULL;
    turncubewidget = NULL;
//    cube = new Cube(this);
//    cube->setParent(this);
    //qDebug() << cubedata->front->color[1][2];

    timer = new QTimer(this);

    flag = false;
    //按钮的链接
    if(true){
        //创建三阶魔方菜单项
        connect(ui->actionthreeorder,&QAction::triggered,[=]() mutable {
            if(flag){
                if(QMessageBox::Yes == QMessageBox::question(this,"question","您已创建一个魔方,是否重新创建",QMessageBox::Yes|QMessageBox::No,QMessageBox::No)){
                    delete cubedata;
                    delete cube;
                    delete turncubewidget;
                    if(debugMode != NULL)delete debugMode;

                    timer->stop();
                    second = 0;
                    minute = 0;
                    hour = 0;
                    ui->startBtn->show();
                    ui->startBtn1->show();
                    cubedata = new ThreeOrderCube;
                    mainInit();
                }
            }
            else{
                cubedata = new ThreeOrderCube;
                mainInit();
            }
            //qDebug()<<"three" ;
        });
        //创建四阶魔方菜单项
        connect(ui->actionfourorder,&QAction::triggered,[=]() mutable {

            //qDebug()<<cubedata->order;
            if(flag){
                if(QMessageBox::Yes == QMessageBox::question(this,"question","您已创建一个魔方,是否重新创建",QMessageBox::Yes|QMessageBox::No)){
                    delete cubedata;
                    delete cube;
                    delete turncubewidget;
                    if(debugMode != NULL)delete debugMode;

                    timer->stop();
                    second = 0;
                    minute = 0;
                    hour = 0;
                    ui->startBtn->show();
                    ui->startBtn1->show();
                    cubedata = new FourOrderCube;
                    mainInit();
                }
            }
            else{
                cubedata = new FourOrderCube;
                mainInit();
            }

            //qDebug()<<"four" << *flag;

        });


        //开始按钮的链接
        connect(ui->startBtn,&QPushButton::clicked,[=]{
            if(flag){
                ui->startBtn->hide();
                ui->startBtn1->hide();
                turncubewidget->show();
                //timer->start(1000);
            }
            else{
                QMessageBox::information(this,"提示","请先创建魔方");
            }
        });
        //打乱并开始
        connect(ui->startBtn1,&QPushButton::clicked,[=]{
            if(flag){
                ui->startBtn->hide();
                ui->startBtn1->hide();
                turncubewidget->show();
                cubedata->upsetCube();
                cube->drawCube(cubedata);
                timer->start(1000);
            }
            else{
                QMessageBox::information(this,"提示","请先创建魔方");
            }
        });

        //计时器的链接
        connect(timer,&QTimer::timeout,[=]{

            second ++;
            if(second >= 60){
                second = 0;
                minute ++;
            }
            if(minute >= 60 && second >= 60){
                second = 0;
                minute = 0;
                hour++;
            }
            QString str = QString("用时:%1:%2:%3").arg(QString::number(hour)).arg(QString::number(minute)).arg(QString::number(second));
            //qDebug()<<str;
            //timeLabel每隔1秒+1
            turncubewidget->timeLabel->setText(str);
        });



        //重置
        connect(ui->actionReset,&QAction::triggered,[=]()mutable{
            if(flag){
                cubedata->resetCube();
                cube->drawCube(cubedata);
            }
            else{
                QMessageBox::information(this,"提示","请先创建魔方");
            }

        });
        //打乱
        connect(ui->actionUpset,&QAction::triggered,[=]()mutable{
            if(flag){
                cubedata->upsetCube();
                cube->drawCube(cubedata);
            }
            else{
                QMessageBox::information(this,"提示","请先创建魔方");
            }

        });

        //调试模式
        connect(ui->debugMode,&QAction::triggered,[=]()mutable{
            if(flag){
                debugMode = new DebugMode(cubedata,cube);
                debugMode->show();
            }
            else{
                QMessageBox::information(this,"提示","请先创建魔方");
            }
        });


    }
}
void MainWindow::mainInit(){


    //为魔方创建数据
    cubedata->setOrder();
    cubedata->init();

    //创建魔方界面
    cube = new Cube(this);
    cube->setParent(this);
    cube->createBlock(cubedata->order);
    cube->drawCube(cubedata);
    cube->show();

    //创建操作界面
    turncubewidget = new TurnCubeWidget(this,cubedata);
    turncubewidget->setParent(this);

    connect(turncubewidget,&TurnCubeWidget::turn,cubedata,&CubeData::turnCube);
    connect(cubedata,&CubeData::turnFinish,[=]{
        cube->drawCube(cubedata);
        if(cubedata->isWin()){
            timer->stop();
            QMessageBox::information(this,"完成!",QString("恭喜你还原完成!!共%1").arg(turncubewidget->timeLabel->text()));
        }
    });
    //判断是否已创建
    flag = true;
}

int MainWindow::second= 0;
int MainWindow::minute= 0;
int MainWindow::hour= 0;

MainWindow::~MainWindow()
{
    delete ui;
}
