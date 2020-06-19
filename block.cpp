#include "block.h"
#include <QDebug>
#include <QPixmap>
//Block::Block(QWidget *parent) : QLabel(parent)
//{

//}

Block::Block(){

}


void Block::setPath(QString blockImg,int order){
    QPixmap pix;
    bool ret = pix.load(blockImg);
    if(!ret){
        qDebug()<<"图片加载失败";
        return;
    }
    float m_order = order;

    //设置图片固定大小
    this->setFixedSize(pix.width()*(0.45/m_order),pix.height()*(0.45/m_order));
    //设置图片
    this->setPixmap(pix);
    //使内容全充满
    this->setScaledContents(true);
    //this->setMask(pix.mask());
    //设置不规则图片的样式
    this->setStyleSheet("QLabel{border:0px;}");

}
