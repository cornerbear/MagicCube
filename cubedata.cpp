#include "cubedata.h"
#include <QString>
#include "block.h"
#include <QDebug>
#include <QMessageBox>
#include <cstdlib>
#include <ctime>
CubeData::CubeData(QObject *parent) : QObject(parent)
{
    order = 3;
}
void CubeData::setOrder(){
    qDebug()<<"setorder";
}

void CubeData::init(){
    //qDebug()<<"init";
    front = new Side("red", "front", order);
    back = new Side("orange", "front", order);
    left = new Side("blue", "right", order);
    right = new Side("green", "right", order);
    up = new Side("yellow", "up", order);
    down = new Side("white", "up", order);
}
void CubeData::turnCube(QString turn){
    int num =turn.toInt();
    switch (num) {
    case 210: _turnLeft();history.push(110);break;    //第二位数代表旋转面,1代表左面(右面),2代表上面(下面),3代表前面(后面)
    case 110: turnLeft();history.push(210);break;     //第三位代表将旋转的层数,0代表第0层(意味着真实的第一层(顺序为从左到右,从前到后,从上到下))
    case 211: _turnLeftMid();history.push(111);break;       //第一位代表顺逆时针,1代表顺时针,2代表逆时针
    case 111: turnLeftMid();history.push(211);break;
    case 212: turnRight();history.push(112);break;
    case 112: _turnRight();history.push(212);break;

    case 120: turnUp();history.push(220);break;
    case 220: _turnUp();history.push(120);break;
    case 121: turnUpMid();history.push(221);break;
    case 221: _turnUpMid();history.push(121);break;
    case 122: _turnDown();history.push(222);break;
    case 222: turnDown();history.push(122);break;

    case 130: _turnFront();history.push(230);break;
    case 230: turnFront();history.push(130);break;
    case 131: _turnFrontMid();history.push(231);break;
    case 231: turnFrontMid();history.push(131);break;
    case 132: turnBack();history.push(232);break;
    case 232: _turnBack();history.push(132);break;
    default:
        break;
    }
    emit turnFinish();
    qDebug()<<"turnfinish";
}

bool CubeData::isWin(){
    bool flag = true;
    QString tempColor;
    QString tempPosition;
    for(int i = 0; i < order; i++){
        for(int j = 0; j < order; j++){
            tempColor = front->color[0][0];
            tempPosition = front->position[0][0];
            if(tempColor != front->color[i][j] || tempPosition != front->position[i][j]){
                flag = false;
            }
            tempColor = back->color[0][0];
            tempPosition = back->position[0][0];
            if(tempColor != back->color[i][j] || tempPosition != back->position[i][j]){
                flag = false;
            }
            tempColor = up->color[0][0];
            tempPosition = up->position[0][0];
            if(tempColor != up->color[i][j] || tempPosition != up->position[i][j]){
                flag = false;
            }
            tempColor = down->color[0][0];
            tempPosition = down->position[0][0];
            if(tempColor != down->color[i][j] || tempPosition != down->position[i][j]){
                flag = false;
            }
            tempColor = left->color[0][0];
            tempPosition = left->position[0][0];
            if(tempColor != left->color[i][j] || tempPosition != left->position[i][j]){
                flag = false;
            }
            tempColor = right->color[0][0];
            tempPosition = right->position[0][0];
            if(tempColor != right->color[i][j] || tempPosition != right->position[i][j]){
                flag = false;
            }
            if(flag == false) return false;//如果判断到有错误直接返回false
        }
    }
    qDebug()<<"胜利!";
    return flag;
}
//重置
void CubeData::resetCube(){
    delete front;
    delete back;
    delete left;
    delete right;
    delete up;
    delete down;

    front = new Side("red", "front", order);
    back = new Side("orange", "front", order);
    left = new Side("blue", "right", order);
    right = new Side("green", "right", order);
    up = new Side("yellow", "up", order);
    down = new Side("white", "up", order);
}
//打乱
void CubeData::upsetCube(){
    srand((int)time(0));
    for(int i = 0; i < 20; i++){
        int num = rand()%18;
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
        default:
            break;
        }
    }
    while (!history.empty()){//清空栈
            history.pop();
    }
}

//交换
void CubeData::swap(QString& s1, QString& s2) {
    QString temp;
    temp = s1; s1 = s2; s2 = temp;
}

//转动魔方的函数
//front
void CubeData::turnFront() {


    //面的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {	//转置
        for (int j = 0; j < i; j++) {
            swap(front->color[i][j], front->color[j][i]);
        }
    }
    for (int i = 0; i < order; i++) {	//水平翻转
        for (int j = 0; j < order / 2; j++) {
            swap(front->color[i][j], front->color[i][order - 1 - j]);
        }
    }
    //边的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {   //转置两条边，up和left
        //up和left
        swap(up->color[order - 1][i], left->color[i][order - 1]);
        //right和down
        swap(right->color[i][0], down->color[0][i]);
    }
    //水平翻转
    for (int i = 0; i < order; i++) {	//水平翻转left和right
        swap(left->color[i][order - 1], right->color[i][0]);
    }
    for (int i = 0; i < order / 2; i++) {	//水平翻转up和down
        //up
        swap(up->color[order - 1][i], up->color[order - 1][order - 1 - i]);
        //down
        swap(down->color[0][i], down->color[0][order - 1 - i]);
    }
}
//back
void CubeData::turnBack() {

    QString temp;

    //面的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {	//转置
        for (int j = 0; j < i; j++) {
            swap(back->color[i][j], back->color[j][i]);
        }
    }
    for (int i = 0; i < order; i++) {	//水平翻转
        for (int j = 0; j < order / 2; j++) {
            swap(back->color[i][j], back->color[i][order - 1 - j]);
        }
    }
    //边的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {
        int j = order - 1;
        temp = right->color[i][j];
        right->color[i][j] = down->color[j][j-i];
        down->color[j][j-i] = left->color[j-i][0];
        left->color[j-i][0] = up->color[0][i];
        up->color[0][i] = temp;
    }
}
//left
void CubeData::turnLeft() {
    //qDebug()<< "左顺" ;

    QString temp;

    //面的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {	//转置
        for (int j = 0; j < i; j++) {
            swap(left->color[i][j], left->color[j][i]);
        }
    }
    for (int i = 0; i < order; i++) {	//水平翻转
        for (int j = 0; j < order / 2; j++) {
            swap(left->color[i][j], left->color[i][order - 1 - j]);
        }
    }
    //边的旋转---------------------------------------------------

    for (int i = 0; i < order; i++) {
        temp = down->color[i][0];
        down->color[i][0] = front->color[i][0];
        front->color[i][0] = up->color[i][0];
        up->color[i][0] = back->color[i][0];
        back->color[i][0] = temp;
    }
}
//right
void CubeData::turnRight() {

    //qDebug()<< "右顺" ;
    QString temp;

    //面的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {	//转置
        for (int j = 0; j < i; j++) {
            swap(right->color[i][j], right->color[j][i]);
        }
    }
    for (int i = 0; i < order; i++) {	//水平翻转
        for (int j = 0; j < order / 2; j++) {
            swap(right->color[i][j], right->color[i][order - 1 - j]);
        }
    }
    //边的旋转---------------------------------------------------

    for (int i = 0; i < order; i++) {
        int j = order - 1;
        temp = back->color[i][j];
        back->color[i][j] = up->color[i][j];
        up->color[i][j] = front->color[i][j];
        front->color[i][j] = down->color[i][j];
        down->color[i][j] = temp;
    }
}
//up
void CubeData::turnUp() {

    QString temp;

    //面的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {	//转置
        for (int j = 0; j < i; j++) {
            swap(up->color[i][j], up->color[j][i]);
        }
    }
    for (int i = 0; i < order; i++) {	//水平翻转
        for (int j = 0; j < order / 2; j++) {
            swap(up->color[i][j], up->color[i][order - 1 - j]);
        }
    }
    //边的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {
        int j = order - 1;

        temp = left->color[0][i];
        left->color[0][i] = front->color[0][i];
        front->color[0][i] = right->color[0][i];
        right->color[0][i] = back->color[j][j - i];
        back->color[j][j - i] = temp;

    }
}
//down
void CubeData::turnDown() {

   // qDebug()<< "下顺" ;
    QString temp;

    //面的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {	//转置
        for (int j = 0; j < i; j++) {
            swap(down->color[i][j], down->color[j][i]);
        }
    }
    for (int i = 0; i < order; i++) {	//水平翻转
        for (int j = 0; j < order / 2; j++) {
            swap(down->color[i][j], down->color[i][order - 1 - j]);
        }
    }
    //边的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {
        int j = order - 1;
        temp = right->color[j][i];
        right->color[j][i] = front->color[j][i];
        front->color[j][i] = left->color[j][i];
        left->color[j][i] = back->color[0][j - i];
        back->color[0][j - i] = temp;
    }
}

//逆时针
void CubeData::_turnFront() {

     QString temp;
    //面的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {	//转置
        for (int j = 0; j < i; j++) {
            swap(front->color[i][j], front->color[j][i]);
        }
    }
    for (int i = 0; i < order; i++) {	//水平翻转
        for (int j = 0; j < order / 2; j++) {
            swap(front->color[j][i], front->color[order - 1 - j][i]);
        }
    }
    //边的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {
        int j = order - 1;
        temp = right->color[i][0];
        right->color[i][0] = down->color[0][j-i];
        down->color[0][j-i] = left->color[j-i][j];
        left->color[j-i][j] = up->color[j][i];
        up->color[j][i] = temp;
    }

}
void CubeData::_turnBack() {

    QString temp;

    //面的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {	//转置
        for (int j = 0; j < i; j++) {
            swap(back->color[i][j], back->color[j][i]);
        }
    }
    for (int i = 0; i < order/2; i++) {	//垂直翻转
        for (int j = 0; j < order; j++) {
            swap(back->color[i][j], back->color[order - 1-i][j]);
        }
    }
    //边的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {
        int j = order - 1;
        temp = up->color[0][i];
        up->color[0][i] = left->color[j-i][0];
        left->color[j-i][0] = down->color[j][j-i];
        down->color[j][j-i] = right->color[i][j];
        right->color[i][j] = temp;
    }

}
void CubeData::_turnLeft() {

    QString temp;

    //面的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {	//转置
        for (int j = 0; j < i; j++) {
            swap(left->color[i][j], left->color[j][i]);
        }
    }
    for (int i = 0; i < order/2; i++) {	//垂直翻转
        for (int j = 0; j < order; j++) {
            swap(left->color[i][j], left->color[order - 1-i][j]);
        }
    }
    //边的旋转---------------------------------------------------

    for (int i = 0; i < order; i++) {
        temp = back->color[i][0];
        back->color[i][0] = up->color[i][0];
        up->color[i][0] = front->color[i][0];
        front->color[i][0] = down->color[i][0];
        down->color[i][0] = temp;
    }
}
void CubeData::_turnRight() {

    QString temp;

    //面的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {	//转置
        for (int j = 0; j < i; j++) {
            swap(right->color[i][j], right->color[j][i]);
        }
    }
    for (int i = 0; i < order/2; i++) {	//垂直翻转
        for (int j = 0; j < order; j++) {
            swap(right->color[i][j], right->color[order - 1 - i][j]);
        }
    }
    //边的旋转---------------------------------------------------

    for (int i = 0; i < order; i++) {
        int j = order - 1;
        temp = down->color[i][j];
        down->color[i][j] = front->color[i][j];
        front->color[i][j] = up->color[i][j];
        up->color[i][j] = back->color[i][j];
        back->color[i][j] = temp;
    }
}
void CubeData::_turnUp() {

    QString temp;

    //面的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {	//转置
        for (int j = 0; j < i; j++) {
            swap(up->color[i][j], up->color[j][i]);
        }
    }
    for (int i = 0; i < order/2; i++) {	//水平翻转
        for (int j = 0; j < order; j++) {
            swap(up->color[i][j], up->color[order - 1 -i][j]);
        }
    }
    //边的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {
        int j = order - 1;

        temp = back->color[j][j - i];
        back->color[j][j - i] = right->color[0][i];
        right->color[0][i] = front->color[0][i];
        front->color[0][i] = left->color[0][i];
        left->color[0][i] = temp;

    }
}
void CubeData::_turnDown() {

    QString temp;

    //面的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {	//转置
        for (int j = 0; j < i; j++) {
            swap(down->color[i][j], down->color[j][i]);
        }
    }
    for (int i = 0; i < order/2; i++) {	//水平翻转
        for (int j = 0; j < order; j++) {
            swap(down->color[i][j], down->color[order - 1 - i][j]);
        }
    }
    //边的旋转---------------------------------------------------
    for (int i = 0; i < order; i++) {
        int j = order - 1;
        temp = back->color[0][j - i];
        back->color[0][j - i] = left->color[j][i];
        left->color[j][i] = front->color[j][i];
        front->color[j][i] = right->color[j][i];
        right->color[j][i] = temp;
    }
}
//中层
void CubeData::turnFrontMid(){

    QString temp;

    for (int i = 0; i < order; i++) {
        int j = order /2;
        temp = right->color[i][j];
        right->color[i][j] = up->color[j][i];
        up->color[j][i] = left->color[order-1-i][j];
        left->color[order-1-i][j] = down->color[j][order-1-i];
        down->color[j][order-1-i] = temp;
    }
}

void CubeData::_turnFrontMid(){

    QString temp;

    for (int i = 0; i < order; i++) {
        int j = order /2;
        temp = down->color[j][order-1-i];
        down->color[j][order-1-i] = left->color[order-1-i][j];
        left->color[order-1-i][j] = up->color[j][i];
        up->color[j][i] = right->color[i][j];
        right->color[i][j] = temp;
    }
}
void CubeData::turnLeftMid(){

    QString temp;

    for (int i = 0; i < order; i++) {
        int j = order /2;
        temp = front->color[i][j];
        front->color[i][j] = up->color[i][j];
        up->color[i][j] = back->color[i][j];
        back->color[i][j] = down->color[i][j];
        down->color[i][j] = temp;
    }

}
void CubeData::_turnLeftMid(){

    QString temp;
    for (int i = 0; i < order; i++) {
        int j = order /2;
        temp = down->color[i][j];
        down->color[i][j] = back->color[i][j];
        back->color[i][j] = up->color[i][j];
        up->color[i][j] = front->color[i][j];
        front->color[i][j] = temp;
    }

}
void CubeData::turnUpMid(){

    QString temp;

    for (int i = 0; i < order; i++) {
        int j = order /2;
        temp = front->color[j][i];
        front->color[j][i] = right->color[j][i];
        right->color[j][i] = back->color[j][order-1-i];
        back->color[j][order-1-i] = left->color[j][i];
        left->color[j][i] = temp;
    }
}
void CubeData::_turnUpMid(){

    QString temp;

    for (int i = 0; i < order; i++) {
        int j = order /2;
        temp = left->color[j][i];
        left->color[j][i] = back->color[j][order-1-i];
        back->color[j][order-1-i] = right->color[j][i];
        right->color[j][i] = front->color[j][i];
        front->color[j][i] = temp;
    }
}
void CubeData::turnFrontMid1(){

}

void CubeData::_turnFrontMid1(){

}
void CubeData::turnLeftMid1(){

}
void CubeData::_turnLeftMid1(){

}
void CubeData::turnUpMid1(){

}
void CubeData::_turnUpMid1(){

}
void CubeData::reTurnCube(QString turn){
    int num =turn.toInt();
    switch (num) {
    case 210: _turnLeft();break;    //第二位数代表旋转面,1代表左面(右面),2代表上面(下面),3代表前面(后面)
    case 110: turnLeft();break;     //第三位代表将旋转的层数,0代表第0层(意味着真实的第一层(顺序为从左到右,从前到后,从上到下))
    case 211: _turnLeftMid();break;       //第一位代表顺逆时针,1代表顺时针,2代表逆时针
    case 111: turnLeftMid();break;
    case 212: turnRight();break;
    case 112: _turnRight();break;

    case 120: turnUp();break;
    case 220: _turnUp();break;
    case 121: turnUpMid();break;
    case 221: _turnUpMid();break;
    case 122: _turnDown();break;
    case 222: turnDown();break;

    case 130: _turnFront();break;
    case 230: turnFront();break;
    case 131: _turnFrontMid();break;
    case 231: turnFrontMid();break;
    case 132: turnBack();break;
    case 232: _turnBack();break;
    default:
        break;
    }
    emit turnFinish();
    qDebug()<<"turnfinish";
}

void CubeData::showCube() {
    //back
    for (int i = 0; i < order; i++) {

        for (int j = 0; j < order; j++) {
            qDebug() << back->color[i][j];
        }

    }
    qDebug() <<"-------";
    //up
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) qDebug() << "  ";
        for (int j = 0; j < order; j++) {
            qDebug() << up->color[i][j];
        }

    }
    for (int i = 0; i < 3; i++) {
        qDebug() <<"-------";
        //打印left
        for (int j = 0; j < order; j++) {
            qDebug() << left->color[i][j];
        }qDebug() <<"-------";
        //打印front
        for (int j = 0; j < order; j++) {
            qDebug() << front->color[i][j];
        }qDebug() <<"-------";
        //打印right
        for (int j = 0; j < order; j++) {
            qDebug() << right->color[i][j];
        }

    }
    //down
    qDebug() <<"-------";
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) qDebug() << "  ";
        for (int j = 0; j < order; j++) {
            qDebug() << down->color[i][j];
        }
qDebug() <<"-------";
    }
}
