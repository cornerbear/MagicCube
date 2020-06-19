/*
 * 用于创建各个面的数据,然后各个面再去使用"块"去画图
 *
 *
 */

#ifndef CUBE_H
#define CUBE_H

#include <QWidget>
#include "cubedata.h"
#include "blockdata.h"
#include <QLabel>
class Cube : public QWidget
{
    Q_OBJECT
public:
    Cube(QWidget *parent);

    void createBlock(int order);
    void drawCube(CubeData * cube);

    void paintEvent(QPaintEvent *event);

    QLabel *backgroundLabel;

    BlockData * frontBlock;
    BlockData * backBlock;
    BlockData * upBlock;
    BlockData * downBlock;
    BlockData * leftBlock;
    BlockData * rightBlock;
    int order;

signals:

public slots:
};

#endif // CUBE_H
