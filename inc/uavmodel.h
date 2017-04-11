#ifndef UAVMODEL_H
#define UAVMODEL_H

#include <qstring.h>

class UAVModel
{
public:
    UAVModel();
    UAVModel(uint8_t nState, uint8_t nControl, float deltat, QString modelPath, QString modelName);

public:
    uint8_t nState;
    uint8_t nControl;
    float deltat;
    QString modelPath;
    QString modelName;
};

#endif // UAVMODEL_H
