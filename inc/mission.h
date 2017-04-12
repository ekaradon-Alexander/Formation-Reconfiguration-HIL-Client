#ifndef MISSION_H
#define MISSION_H

#include <QVector>

struct InitTarget
{
    uint8_t ID;
    float *location;
};

typedef struct InitTarget Initial;
typedef struct InitTarget Target;

class Mission
{
public:
    Mission();

    QVector<Initial> initial;
    QVector<Target> target;

    void addMissionItem(uint8_t ID, QString initState, QString targetState);

};

#endif // MISSION_H
