/*
 * 用于每个块的数据显示
 *
 *
 */

#ifndef BLOCK_H
#define BLOCK_H

#include <QLabel>
using namespace std;

class Block : public QLabel
{
    Q_OBJECT
public:
    //explicit Block(QWidget *parent = nullptr);
    Block();
    void setPath(QString blockImg,int order);

signals:

public slots:
};

#endif // BLOCK_H
