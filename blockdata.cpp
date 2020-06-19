#include "blockdata.h"

BlockData::BlockData(int order):
    order(order)
{
    //开辟二维数组
    block = new Block * [this->order];
    for (int i = 0; i < this->order; i++) {
        block[i] = new Block[this->order];
    }

}
