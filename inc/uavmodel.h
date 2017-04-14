#ifndef UAVMODEL_H
#define UAVMODEL_H

#include <qstring.h>
#include <QTimer>

class UAVModel
{
public:
    UAVModel();
    UAVModel(uint8_t nModelState, uint8_t nModelControl, float deltat, QString modelPath, QString modelName);

public:
    uint8_t nModelState;
    uint8_t nModelControl;
    float deltat;
    QString modelPath;
    QString modelName;
};

#endif // UAVMODEL_H
