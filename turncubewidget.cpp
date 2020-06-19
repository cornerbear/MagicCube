#include "turncubewidget.h"
#include <QPushButton>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QFont>
#include <QMessageBox>
TurnCubeWidget::TurnCubeWidget(QWidget *parent,CubeData* cubedata)
    : order(cubedata->order)
{
    setFixedSize(331,571);
    this->move(770,0);



    timeLabel = new QLabel;
    timeLabel->setParent(this);
    timeLabel->setFixedSize(331,100);
    timeLabel->move(0,0);
    timeLabel->setAlignment(Qt::AlignCenter);

    QString str = QString("用时:0:0:0");
    timeLabel->setText(str);
    QFont font("Microsoft YaHei",20,75);
    timeLabel->setFont(font);
    timeLabel->show();

    history = new QPushButton;
    history->setParent(this);
    history->setFixedSize(120,50);
    history->move(100,480);
    history->setText("上一步");
    history->show();

    for(int i = 0; i < order; i++){
        for(int j = 0; j < order; j++){

            int tempX = 25;
            int tempY = 200;

            int k = 0;

            //上
            Block *up  = new Block;
            up->setPath(":/res/yellowup.png",order);
            up->setParent(this);
            up->show();

            tempX += (order - 1) * up->height();

            up->move(tempX + j*up->width() - up->height()*(i+j),tempY + i*up->height());

            k = 0;
            QString str = QString("21%1");//第一个1代表顺,第二个1代表左面,第三个数代表第j层
            while((i == 0||i == order-1) && k < order){
                QPushButton * btn = new QPushButton;
                btn->setFixedSize(21,21);
                if(i == 0){
                    btn->setText("↑");
                }
                if(i == order-1){
                    btn->setText("↓");
                    str = QString("11%1");
                }
                btn->setParent(this);
                btn->move(tempX+(up->width()-btn->width())/2 + j*up->width() - up->height()*(i+j),tempY+(up->height()-btn->width())/2 + i*up->height());
                btn->show();
                k++;
                connect(btn,&QPushButton::clicked,[=]{
                   emit this->turn(str.arg(j));
                    qDebug()<<str.arg(j);
                });
            }
            //qDebug()<<up->height()<<up->width();
            //前
            tempX -= (order - 1) * up->height();
            tempY += order * up->height();

            Block *front  = new Block;
            front->setPath(":/res/redfront.png",order);
            front->setParent(this);
            front->show();
            front->move(tempX + j*front->width(),tempY + i*front->height());

            k = 0;
            str = QString("12%1");
            while((j == 0||j == order-1) && k < order){
                QPushButton * btn = new QPushButton;
                btn->setFixedSize(21,21);
                if(j == 0){
                    btn->setText("←");
                }
                if(j == order-1){
                    btn->setText("→");
                    str = QString("22%1");
                }
                btn->setParent(this);
                btn->move(tempX+(front->width()-btn->width())/2 + j*front->width(),tempY+(front->height()-btn->width())/2 + i*front->height());
                btn->show();
                k++;
                connect(btn,&QPushButton::clicked,[=]{
                   emit this->turn(str.arg(i));
                   qDebug()<<str.arg(i);
                });
            }
            //qDebug()<<front->height()<<front->width();
            //右
            tempX += order * front->width();

            Block *right  = new Block;
            right->setPath(":/res/greenright.png",order);
            right->setParent(this);
            right->show();

            tempY -= right->width();//向上偏移一个小长度

            right->move(tempX + j*right->width(),tempY+ i*right->height() - right->width()*(i+j));

            k = 0;
            str = QString("13%1");
            while((i == 0||i == order-1) && k < order){
                QPushButton * btn = new QPushButton;
                btn->setFixedSize(21,21);
                if(i == 0){
                    btn->setText("↑");
                }
                if(i == order-1){
                    btn->setText("↓");
                    str = QString("23%1");
                }
                btn->setParent(this);
                btn->move(tempX+(right->width()-btn->width())/2 + j*right->width(),tempY+(right->height()-btn->width())/2+ i*right->height() - right->width()*(i+j));
                btn->show();
                k++;
                connect(btn,&QPushButton::clicked,[=]{
                   emit this->turn(str.arg(j));
                   qDebug()<<str.arg(j);
                });
            }

        }
    }

    connect(history,&QPushButton::clicked,[=]{
        if(!cubedata->history.empty()){
            cubedata->reTurnCube(QString::number(cubedata->history.top()));
            cubedata->history.pop();
        }
        else QMessageBox::information(this,"提示","当前没有上一步");

    });

}
