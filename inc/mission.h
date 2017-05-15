#ifndef MISSION_H
#define MISSION_H

#include <QVector>
#include <common.h>

typedef struct
{
    uint8_t ID;
    float state[MAX_STATE_NUMBER];
} Initial;

typedef struct
{
    uint8_t ID;
    float offsetLocation[LOC_STATE_NUMBER];
} Target;

class Mission
{
public:
    Mission();

    float targetCenterVelocy;
    float targetCenterDirection;
    float targetCenterLocation[LOC_STATE_NUMBER];

    QVector<Initial *> initial;
    QVector<Target *> target;

    void updateMissionCenter(float targetCenterVelocy, float targetCenterDirection);
    void updateMissionItem(uint8_t ID, QVector<float> initState, QVector<float> targetState);
    void dispMissionItem(void);
};

#endif // MISSION_H
