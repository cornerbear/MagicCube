#ifndef SIDE_H
#define SIDE_H


#include <QString>

class Side
{

public:
    Side(QString color, QString position, int order);

    QString ** color; //二维指针
    QString** position; //二维指针

    int order;


};

#endif // SIDE_H
