#ifndef TURNCUBEWIDGET_H
#define TURNCUBEWIDGET_H

#include <QWidget>
#include "block.h"
#include <QLabel>
#include <QPushButton>
#include "cubedata.h"
class TurnCubeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TurnCubeWidget(QWidget *parent,CubeData* cubedata);



    int order;
    QLabel* timeLabel;
    QPushButton * history;
signals:

    void turn(QString position);
public slots:
};

#endif // TURNCUBEWIDGET_H
