#include "mission.h"
#include <QDebug>

Mission::Mission()
{

}

void Mission::updateMissionCenter(float targetCenterVelocy, float targetCenterDirection)
{
    this->targetCenterVelocy = targetCenterVelocy;
    this->targetCenterDirection = targetCenterDirection;
}

void Mission::updateMissionItem(uint8_t ID, QVector<float> initState,
                                QVector<float> targetState)
{
    Initial *tempInitial = new Initial();
    tempInitial->ID = ID;
    for (uint8_t i = 0; i < MAX_STATE_NUMBER; i++)
    {
        tempInitial->state[i] = initState.at(i);
    }

    bool exist = false;
    foreach (Initial *in, initial)
    {
        if (in->ID == tempInitial->ID)  // initial states changed
        {
            exist = true;
            for (uint8_t i = 0; i < MAX_STATE_NUMBER; i++)
            {
                in->state[i] = initState.at(i);
            }
            break;
        }
    }
    if (!exist)
    {
        initial.append(tempInitial);
    }

    Target *tempTarget = new Target();
    tempTarget->ID = ID;
    for (uint8_t i = 0; i < LOC_STATE_NUMBER; i++)
    {
        tempTarget->offsetLocation[i] = targetState.at(i);
    }

    exist = false;
    foreach (Target *ta, target)
    {
        if (ta->ID == tempTarget->ID)   // target location changed
        {
            exist = true;
            for (uint8_t i = 0; i < LOC_STATE_NUMBER; i++)
            {
                ta->offsetLocation[i] = targetState.at(i);
            }
            break;
        }
    }
    if (!exist)
    {
        target.append(tempTarget);
    }

    targetCenterLocation[0] = 0.0;
    targetCenterLocation[1] = 0.0;
    targetCenterLocation[2] = 0.0;

    foreach (Target *ta, target)
    {
        for (uint8_t i = 0; i < LOC_STATE_NUMBER; i++)
        {
            targetCenterLocation[i] += ta->offsetLocation[i];
        }
    }

    for (uint8_t i = 0; i < LOC_STATE_NUMBER; i++)
    {
        targetCenterLocation[i] /= static_cast<float>(target.length());
    }
}

void Mission::dispMissionItem()
{
    QString str;
    foreach (Initial *in, initial)
    {
        str = QString("Initial state of %1: (").arg(in->ID);
        for (int x = 0; x < MAX_STATE_NUMBER; x++)
        {
            str += (QString::number(in->state[x]) + "  ");
        }
        str += ")";
        qDebug() << str;
    }

    foreach (Target *ta, target)
    {
        str = QString("Target state of %1: (").arg(ta->ID);
        for (int x = 0; x < LOC_STATE_NUMBER; x++)
        {
            str += (QString::number(ta->offsetLocation[x]) + "  ");
        }
        str += ")";
        qDebug() << str;
    }
}
