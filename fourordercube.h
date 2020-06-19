#ifndef FOURORDERCUBE_H
#define FOURORDERCUBE_H

#include <cubedata.h>

class FourOrderCube : public CubeData
{
public:
    FourOrderCube();
    //设置魔方的阶数
    void setOrder();

    void upsetCube();
    void turnCube(QString turn);
    void reTurnCube(QString turn);

    //中层   从左往右,右为1
    void turnFrontMid();
    void _turnFrontMid();
    void turnLeftMid();
    void _turnLeftMid();
    void turnUpMid();
    void _turnUpMid();

    void turnFrontMid1();
    void _turnFrontMid1();
    void turnLeftMid1();
    void _turnLeftMid1();
    void turnUpMid1();
    void _turnUpMid1();
};

#endif // FOURORDERCUBE_H
