#include "debugmode.h"
#include <QTextEdit>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
DebugMode::DebugMode(CubeData * cubedata,Cube *cube){


    setFixedSize(500,500);
    this->setWindowIcon(QPixmap(":/res/cube.png"));
    this->setWindowTitle("调试模式");

    QTextEdit* edit = new QTextEdit;
    edit->setParent(this);
    edit->setFixedSize(450,200);
    edit->move(25,25);

    QPushButton* btn = new QPushButton;
    btn->setParent(this);
    btn->setFixedSize(250,200);
    btn->move(125,275);
    btn->setText("提交");
    connect(btn,&QPushButton::clicked,[=]()mutable{

        QString str = edit->toPlainText();
        qDebug()<<str;
        QStringList strList = str.split(" ");
        for(int i = 0;i < strList.length();++i){
            qDebug()<<strList[i];
            if (strList[i] == "F")  cubedata->turnFront();
            else if (strList[i] == "B")  cubedata->turnBack();
            else if (strList[i] == "U")  cubedata->turnUp();
            else if (strList[i] == "D")  cubedata->turnDown();
            else if (strList[i] == "R")  cubedata->turnRight();
            else if (strList[i] == "L")  cubedata->turnLeft();
            else if (strList[i] == "F_")  cubedata->_turnFront();
            else if (strList[i] == "B_")  cubedata->_turnBack();
            else if (strList[i] == "U_")  cubedata->_turnUp();
            else if (strList[i] == "D_")  cubedata->_turnDown();
            else if (strList[i] == "R_")  cubedata->_turnRight();
            else if (strList[i] == "L_")  cubedata->_turnLeft();
            else if (strList[i] == "FM")  cubedata->turnFrontMid();
            else if (strList[i] == "FM_")  cubedata->_turnFrontMid();
            else if (strList[i] == "LM")  cubedata->turnLeftMid();
            else if (strList[i] == "LM_")  cubedata->_turnLeftMid();
            else if (strList[i] == "UM")  cubedata->turnUpMid();
            else if (strList[i] == "UM_")  cubedata->_turnUpMid();
            else if (strList[i] == "FM1"){
                if(cubedata->order == 4){
                    cubedata->turnFrontMid1();
                }
                else QMessageBox::warning(this,"警告",QString("当前无%1指令").arg(strList[i]));
            }
            else if (strList[i] == "FM1_"){
                if(cubedata->order == 4){
                    cubedata->_turnFrontMid1();
                }
                else QMessageBox::warning(this,"警告",QString("当前无%1指令").arg(strList[i]));
            }
            else if (strList[i] == "LM1"){
                if(cubedata->order == 4){
                    cubedata->turnLeftMid1();
                }
                else QMessageBox::warning(this,"警告",QString("当前无%1指令").arg(strList[i]));
            }
            else if (strList[i] == "LM1_"){
                if(cubedata->order == 4){
                    cubedata->_turnLeftMid1();
                }
                else QMessageBox::warning(this,"警告",QString("当前无%1指令").arg(strList[i]));
            }
            else if (strList[i] == "UM1"){
                if(cubedata->order == 4){
                    cubedata->turnUpMid1();
                }
                else QMessageBox::warning(this,"警告",QString("当前无%1指令").arg(strList[i]));
            }
            else if (strList[i] == "UM1_"){
                if(cubedata->order == 4){
                    cubedata->_turnUpMid1();
                }
                else QMessageBox::warning(this,"警告",QString("当前无%1指令").arg(strList[i]));
            }
            else QMessageBox::warning(this,"警告",QString("当前无%1指令").arg(strList[i]));
        }
        cube->drawCube(cubedata);
    });
}
