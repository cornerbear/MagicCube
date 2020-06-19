#include "side.h"


Side::Side(QString color, QString position, int order)
    :order(order) {

    this->color = new QString * [order];//开辟指针数组
    this->position = new QString * [order];//开辟指针数组

    for (int i = 0; i < order; i++) {

        this->color[i] = new QString[order];
        this->position[i] = new QString[order];
        for (int j = 0; j < order; j++) {

            this->color[i][j] = color;
            this->position[i][j] = position;
        }
        //block[i][2] = "紫";
    }

}
