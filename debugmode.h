#ifndef DEBUGMODE_H
#define DEBUGMODE_H

#include <QMainWindow>
#include "cubedata.h"
#include "cube.h"
class DebugMode : public QMainWindow
{
    Q_OBJECT
public:
    DebugMode(CubeData * cubedata,Cube *cube);

signals:

public slots:
};

#endif // DEBUGMODE_H
