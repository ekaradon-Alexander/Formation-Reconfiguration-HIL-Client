#include "uavmodel.h"

UAVModel::UAVModel()
{

}

UAVModel::UAVModel(uint8_t nState, uint8_t nControl, float deltat,
                   QString modelPath, QString modelName)
{
    this->nModelState = nState;
    this->nModelControl = nControl;
    this->deltat = deltat;
    this->modelPath = modelPath;
    this->modelName= modelName;
}
