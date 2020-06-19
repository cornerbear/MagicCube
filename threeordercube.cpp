#include "threeordercube.h"
#include <QDebug>
ThreeOrderCube::ThreeOrderCube():CubeData(){

}
void ThreeOrderCube::setOrder() {
    order = 3;
    qDebug()<<"setorder3";
}
