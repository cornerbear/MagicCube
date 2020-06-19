/*
 * 用于每个块的图片数据维护
 *
 *
 */

#ifndef BLOCKDATA_H
#define BLOCKDATA_H
#include "block.h"
using namespace std;

class BlockData
{
public:

    BlockData(int order);

    Block ** block;

    int order;

};

#endif // BLOCKDATA_H
