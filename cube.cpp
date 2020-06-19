#include "cube.h"
#include <QString>
#include "block.h"
#include <QDebug>
#include <QPainter>
Cube::Cube(QWidget *parent) : QWidget(parent)
{

    setFixedSize(771,571);
    this->move(0,25);

}
void Cube::createBlock(int order) {

    //qDebug()<<"createBlock";
    //开辟二维数组
    this->order = order;
    frontBlock = new BlockData(this->order);
    backBlock = new BlockData(this->order);
    leftBlock = new BlockData(this->order);
    rightBlock = new BlockData(this->order);
    upBlock = new BlockData(this->order);
    downBlock = new BlockData(this->order);
}

void Cube::paintEvent(QPaintEvent *event){
    //qDebug()<<"paintevent";
    QPainter painter(this) ;
    painter.drawPixmap(rect(),QPixmap(":/res/background.png"),QRect());
}

void Cube::drawCube(CubeData * cube) {

    //qDebug()<<"drawCube";
    //魔方各个面图片初始化
    for(int i = 0 ; i < order;i++){
        for(int j = 0 ; j < order; j++){

            QString str = QString(":/res/%1%2.png");

            int tempX = 0;
            int tempY = 0;

            //后
            //qDebug()<<"backDraw";
            backBlock->block[i][j].setPath(str.arg(cube->back->color[i][j]).arg(cube->back->position[i][j]),cube->order);
            backBlock->block[i][j].setParent(this);
            backBlock->block[i][j].show();
            backBlock->block[i][j].move(550 + j*backBlock->block[i][j].width(),25+((order-1)*backBlock->block[i][j].height()) - i*backBlock->block[i][j].height());
            //qDebug()<<backBlock->block[i][j].width();

            //左
            leftBlock->block[i][j].setPath(str.arg(cube->left->color[i][j]).arg(cube->left->position[i][j]),cube->order);
            leftBlock->block[i][j].setParent(this);
            leftBlock->block[i][j].show();
            leftBlock->block[i][j].move((55+(order-1)*leftBlock->block[i][j].width()) - j*leftBlock->block[i][j].width(),110 + i*leftBlock->block[i][j].height() - leftBlock->block[i][j].width()*(i+j)+(leftBlock->block[i][j].height() - leftBlock->block[i][j].width())*j);
            //qDebug()<<leftBlock->block[i][j].width() << "---" << leftBlock->block[i][j].height();

            tempX = 55 + order*leftBlock->block[i][j].width() + (order-1)*leftBlock->block[i][j].width();//左画完后的位置
            tempX += 50;//左和中之间的间隔
            //上
            upBlock->block[i][j].setPath(str.arg(cube->up->color[i][j]).arg(cube->up->position[i][j]),cube->order);
            upBlock->block[i][j].setParent(this);
            upBlock->block[i][j].show();
            tempX += (order-1) * upBlock->block[i][j].height();//向右偏移两个小长度
            upBlock->block[i][j].move(tempX + j*upBlock->block[i][j].width() - upBlock->block[i][j].height()*(i+j),110 + i*upBlock->block[i][j].height());
            //qDebug()<<upBlock->block[i][j].width() << "---" << upBlock->block[i][j].height();

            tempX -= (order-1) * upBlock->block[i][j].height();//减去画上时向右偏移的两个小长度
            tempY = 110 + order * upBlock->block[i][j].height();
            //前
            frontBlock->block[i][j].setPath(str.arg(cube->front->color[i][j]).arg(cube->front->position[i][j]),cube->order);
            frontBlock->block[i][j].setParent(this);
            frontBlock->block[i][j].show();
            frontBlock->block[i][j].move(tempX + j*frontBlock->block[i][j].width(),tempY + i*frontBlock->block[i][j].height());

            tempX += order*frontBlock->block[i][j].width();

            //创建右面
            rightBlock->block[i][j].setPath(str.arg(cube->right->color[i][j]).arg(cube->right->position[i][j]),cube->order);
            rightBlock->block[i][j].setParent(this);
            rightBlock->block[i][j].show();
            tempY -= rightBlock->block[i][j].width();//向上偏移一个小长度
            rightBlock->block[i][j].move(tempX + j*rightBlock->block[i][j].width(),tempY+ i*rightBlock->block[i][j].height() - rightBlock->block[i][j].width()*(i+j));


            tempY += rightBlock->block[i][j].width();//还原向上偏移的一个小长度
            tempX = 55 + order*leftBlock->block[i][j].width() + (order-1)*leftBlock->block[i][j].width();//左画完后的位置
            tempY += order*frontBlock->block[i][j].height();//前画完后的位置
            //qDebug()<<tempY;
            //下
            downBlock->block[i][j].setPath(str.arg(cube->down->color[i][j]).arg(cube->down->position[i][j]),cube->order);
            downBlock->block[i][j].setParent(this);
            downBlock->block[i][j].show();
            tempY += (order-1) * downBlock->block[i][j].height();
            downBlock->block[i][j].move(tempX + j*downBlock->block[i][j].width() - downBlock->block[i][j].height()*(i+j)+(downBlock->block[i][j].width() - downBlock->block[i][j].height())*i,tempY + 30 - i*downBlock->block[i][j].height());


        }
    }

}


