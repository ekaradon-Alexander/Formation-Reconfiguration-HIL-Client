#include "mission.h"

Mission::Mission()
{

}

void Mission::addMissionItem(uint8_t ID, QString initState, QString targetState)
{
    QStringList initStateList = initState.split(',');
    Initial *tempInitial = new Initial();
    tempInitial->ID = ID;
    tempInitial->location = new float(initStateList.length());
    for (uint8_t i = 0; i < initStateList.length(); i++)
    {
        tempInitial->location[i] = initStateList.at(i).toFloat();
    }

    QStringList targetStateList = targetState.split(',');
    Target *tempTarget = new Target();
    tempTarget->ID = ID;
    tempTarget->location = new float(targetStateList.length());
    for (uint8_t i = 0; i < targetStateList.length(); i++)
    {
        tempTarget->location[i] = targetStateList.at(i).toFloat();
    }

    initial.append(*tempInitial);
    target.append(*tempTarget);
}
