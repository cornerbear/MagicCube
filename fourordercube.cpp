#include "fourordercube.h"
#include <QDebug>
FourOrderCube::FourOrderCube():CubeData(){

}

void FourOrderCube::setOrder() {
    order = 4;
    qDebug()<<"setorder4";
}

void FourOrderCube::turnCube(QString turn){
    int num =turn.toInt();
    switch (num) {                  //第一位代表顺逆时针,1代表顺时针,2代表逆时针
    case 210: _turnLeft();history.push(110);break;    //第二位数代表旋转面,1代表左面(右面),2代表上面(下面),3代表前面(后面)
    case 110: turnLeft();history.push(210);break;     //第三位代表将旋转的层数,0代表第0层(意味着真实的第一层(顺序为从左到右,从前到后,从上到下))
    case 211: _turnLeftMid();history.push(111);break;
    case 111: turnLeftMid();history.push(211);break;
    case 212: _turnLeftMid1();history.push(112);break;
    case 112: turnLeftMid1();history.push(212);break;
    case 213: turnRight();history.push(113);break;
    case 113: _turnRight();history.push(213);break;

    case 120: turnUp();history.push(220);break;
    case 220: _turnUp();history.push(120);break;
    case 121: turnUpMid();history.push(221);break;
    case 221: _turnUpMid();history.push(121);break;
    case 122: turnUpMid1();history.push(222);break;
    case 222: _turnUpMid1();history.push(122);break;
    case 123: _turnDown();history.push(223);break;
    case 223: turnDown();history.push(123);break;

    case 130: _turnFront();history.push(230);break;
    case 230: turnFront();history.push(130);break;
    case 131: _turnFrontMid();history.push(231);break;
    case 231: turnFrontMid();history.push(131);break;
    case 132: _turnFrontMid1();history.push(232);break;
    case 232: turnFrontMid1();history.push(132);break;
    case 133: turnBack();history.push(233);break;
    case 233: _turnBack();history.push(133);break;
    default:
        break;
    }
    emit turnFinish();
    //qDebug()<<"turnfinish";
}
void FourOrderCube::upsetCube(){
    srand((int)time(0));
    for(int i = 0; i < 20; i++){
        int num = rand()%24;
        //qDebug()<<num;
        switch (num) {
        case 0: turnFront();qDebug()<<"F";break;
        case 1: turnBack();qDebug()<<"B";break;
        case 2: turnUp();qDebug()<<"U";break;
        case 3: turnDown();qDebug()<<"D";break;
        case 4: turnLeft();qDebug()<<"L";break;
        case 5: turnRight();qDebug()<<"R";break;

        case 6: _turnFront();qDebug()<<"F_";break;
        case 7: _turnBack();qDebug()<<"B_";break;
        case 8: _turnUp();qDebug()<<"U_";break;
        case 9: _turnDown();qDebug()<<"D_";break;
        case 10: _turnLeft();qDebug()<<"L_";break;
        case 11: _turnRight();qDebug()<<"R_";break;

        case 12: turnFrontMid();qDebug()<<"FM";break;
        case 13: _turnFrontMid();qDebug()<<"FM_";break;
        case 14: turnLeftMid();qDebug()<<"LM";break;
        case 15: _turnLeftMid();qDebug()<<"LM_";break;
        case 16: turnUpMid();qDebug()<<"UM";break;
        case 17: _turnUpMid();qDebug()<<"UM_";break;

        case 18: turnFrontMid();qDebug()<<"FM1";break;
        case 19: _turnFrontMid();qDebug()<<"FM1_";break;
        case 20: turnLeftMid();qDebug()<<"LM1";break;
        case 21: _turnLeftMid();qDebug()<<"LM1_";break;
        case 22: turnUpMid();qDebug()<<"UM1";break;
        case 23: _turnUpMid();qDebug()<<"UM1_";break;
        default:
            break;
        }
    }
    while (!history.empty()){//清空栈
            history.pop();
    }
}
//中层
//FrontMid
void FourOrderCube::turnFrontMid(){
    QString temp;

    for (int i = 0; i < order; i++) {
        int j = (order-1) /2;
        temp = right->color[i][j];
        right->color[i][j] = up->color[j+1][i];
        up->color[j+1][i] = left->color[order-1-i][j+1];
        left->color[order-1-i][j+1] = down->color[j][order-1-i];
        down->color[j][order-1-i] = temp;
    }
}

void FourOrderCube::_turnFrontMid(){
    QString temp;

    for (int i = 0; i < order; i++) {
        int j = (order-1) /2;
        temp = down->color[j][order-1-i];
        down->color[j][order-1-i] = left->color[order-1-i][j+1];
        left->color[order-1-i][j+1] = up->color[j+1][i];
        up->color[j+1][i] = right->color[i][j];
        right->color[i][j] = temp;
    }
}
//LeftMid
void FourOrderCube::turnLeftMid(){
    QString temp;

    for (int i = 0; i < order; i++) {
        int j = (order-1) /2;
        temp = front->color[i][j];
        front->color[i][j] = up->color[i][j];
        up->color[i][j] = back->color[i][j];
        back->color[i][j] = down->color[i][j];
        down->color[i][j] = temp;
    }
}
void FourOrderCube::_turnLeftMid(){
    QString temp;

    for (int i = 0; i < order; i++) {
        int j = (order-1) /2;
        temp = down->color[i][j];
        down->color[i][j] = back->color[i][j];
        back->color[i][j] = up->color[i][j];
        up->color[i][j] = front->color[i][j];
        front->color[i][j] = temp;
    }

}
//UpMid
void FourOrderCube::turnUpMid(){
    QString temp;

    for (int i = 0; i < order; i++) {
        int j = (order-1) /2;
        temp = front->color[j][i];
        front->color[j][i] = right->color[j][i];
        right->color[j][i] = back->color[j+1][order-1-i];
        back->color[j+1][order-1-i] = left->color[j][i];
        left->color[j][i] = temp;
    }
}
void FourOrderCube::_turnUpMid(){
    QString temp;

    for (int i = 0; i < order; i++) {
        int j = (order-1) /2;
        temp = left->color[j][i];
        left->color[j][i] = back->color[j+1][order-1-i];
        back->color[j+1][order-1-i] = right->color[j][i];
        right->color[j][i] = front->color[j][i];
        front->color[j][i] = temp;
    }
}
//FrontMid1
void FourOrderCube::turnFrontMid1(){
    QString temp;

    for (int i = 0; i < order; i++) {
        int j = order /2;
        temp = right->color[i][j];
        right->color[i][j] = up->color[j-1][i];
        up->color[j-1][i] = left->color[order-1-i][j-1];
        left->color[order-1-i][j-1] = down->color[j][order-1-i];
        down->color[j][order-1-i] = temp;
    }
}

void FourOrderCube::_turnFrontMid1(){
    QString temp;

    for (int i = 0; i < order; i++) {
        int j = order /2;
        temp = down->color[j][order-1-i];
        down->color[j][order-1-i] = left->color[order-1-i][j-1];
        left->color[order-1-i][j-1] = up->color[j-1][i];
        up->color[j-1][i] = right->color[i][j];
        right->color[i][j] = temp;
    }
}
//LeftMid1
void FourOrderCube::turnLeftMid1(){
    QString temp;

    for (int i = 0; i < order; i++) {
        int j = order/2;
        temp = front->color[i][j];
        front->color[i][j] = up->color[i][j];
        up->color[i][j] = back->color[i][j];
        back->color[i][j] = down->color[i][j];
        down->color[i][j] = temp;
    }
}
void FourOrderCube::_turnLeftMid1(){
    QString temp;

    for (int i = 0; i < order; i++) {
        int j = order/2;
        temp = down->color[i][j];
        down->color[i][j] = back->color[i][j];
        back->color[i][j] = up->color[i][j];
        up->color[i][j] = front->color[i][j];
        front->color[i][j] = temp;
    }
}
//UpMid1
void FourOrderCube::turnUpMid1(){
    QString temp;

    for (int i = 0; i < order; i++) {
        int j = order/2;
        temp = front->color[j][i];
        front->color[j][i] = right->color[j][i];
        right->color[j][i] = back->color[j-1][order-1-i];
        back->color[j-1][order-1-i] = left->color[j][i];
        left->color[j][i] = temp;
    }
}
void FourOrderCube::_turnUpMid1(){
    QString temp;

    for (int i = 0; i < order; i++) {
        int j = order/2;
        temp = left->color[j][i];
        left->color[j][i] = back->color[j-1][order-1-i];
        back->color[j-1][order-1-i] = right->color[j][i];
        right->color[j][i] = front->color[j][i];
        front->color[j][i] = temp;
    }
}

void FourOrderCube::reTurnCube(QString turn){
    int num =turn.toInt();
    switch (num) {                  //第一位代表顺逆时针,1代表顺时针,2代表逆时针
    case 210: _turnLeft();break;    //第二位数代表旋转面,1代表左面(右面),2代表上面(下面),3代表前面(后面)
    case 110: turnLeft();break;     //第三位代表将旋转的层数,0代表第0层(意味着真实的第一层(顺序为从左到右,从前到后,从上到下))
    case 211: _turnLeftMid();break;
    case 111: turnLeftMid();break;
    case 212: _turnLeftMid1();break;
    case 112: turnLeftMid1();break;
    case 213: turnRight();break;
    case 113: _turnRight();break;

    case 120: turnUp();break;
    case 220: _turnUp();break;
    case 121: turnUpMid();break;
    case 221: _turnUpMid();break;
    case 122: turnUpMid1();break;
    case 222: _turnUpMid1();break;
    case 123: _turnDown();break;
    case 223: turnDown();break;

    case 130: _turnFront();break;
    case 230: turnFront();break;
    case 131: _turnFrontMid();break;
    case 231: turnFrontMid();break;
    case 132: _turnFrontMid1();break;
    case 232: turnFrontMid1();break;
    case 133: turnBack();break;
    case 233: _turnBack();break;
    default:
        break;
    }
    emit turnFinish();
    //qDebug()<<"turnfinish";
}
