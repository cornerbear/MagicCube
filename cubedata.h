/*
 * 用于魔方各个面的颜色和位置的数据维护,在操作中主要操作这些数据
 *
 *
 */

#ifndef CUBEDATA_H
#define CUBEDATA_H
#include <QObject>

#include "side.h"
#include <stack>
using namespace std;
class CubeData : public QObject
{
    Q_OBJECT
public:
    explicit CubeData(QObject *parent = nullptr);
    virtual void setOrder();
    //初始化魔方
    void init();

    //各个面的信息
    Side* front;
    Side* back;
    Side* left;
    Side* right;
    Side* up;
    Side* down;

    int order;//阶数
    stack<int> history;

    //判断胜利
    bool isWin();

    virtual void turnCube(QString turn);
    virtual void reTurnCube(QString turn);

    void resetCube();
    virtual void upsetCube();

    void swap(QString& s1, QString& s2);

    //顺时针
    virtual void turnFront();
    virtual void turnBack();
    virtual void turnLeft();
    virtual void turnRight();
    virtual void turnUp();
    virtual void turnDown();
    //逆时针
    virtual void _turnFront();
    virtual void _turnBack();
    virtual void _turnLeft();
    virtual void _turnRight();
    virtual void _turnUp();
    virtual void _turnDown();
    //中层
    virtual void turnFrontMid();
    virtual void _turnFrontMid();
    virtual void turnLeftMid();
    virtual void _turnLeftMid();
    virtual void turnUpMid();
    virtual void _turnUpMid();

    virtual void turnFrontMid1();
    virtual void _turnFrontMid1();
    virtual void turnLeftMid1();
    virtual void _turnLeftMid1();
    virtual void turnUpMid1();
    virtual void _turnUpMid1();

    //调试使用
    void showCube();
signals:

    void turnFinish();
public slots:
};

#endif // CUBEDATA_H
