#ifndef MISSION_H
#define MISSION_H

#include <QVector>

struct InitTarget
{
    uint8_t ID;
    uint8_t length;
    float *location;
};

typedef struct InitTarget Initial;
typedef struct InitTarget Target;

class Mission
{
public:
    Mission();

    QVector<Initial *> initial;
    QVector<Target *> target;

    void updateMissionItem(uint8_t ID, QVector<float> initState, QVector<float> targetState);
    void dispMissionItem(void);
};

#endif // MISSION_H
