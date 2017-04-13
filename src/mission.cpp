#include "mission.h"
#include <QDebug>

Mission::Mission()
{

}

void Mission::updateMissionItem(uint8_t ID, QVector<float> initState,
                                QVector<float> targetState)
{
    Initial *tempInitial = new Initial();
    tempInitial->ID = ID;
    tempInitial->location = new float[initState.length()];
    for (uint8_t i = 0; i < initState.length(); i++)
    {
        tempInitial->location[i] = initState.at(i);
    }
    tempInitial->length = initState.length();

    bool exist = false;
    foreach (Initial *in, initial)
    {
        if (in->ID == tempInitial->ID)
        {
            exist = true;
            in->length = tempInitial->length;
            delete[] in->location;
            in->location = tempInitial->location;
            break;
        }
    }
    if (!exist)
    {
        initial.append(tempInitial);
    }

    Target *tempTarget = new Target();
    tempTarget->ID = ID;
    tempTarget->location = new float[targetState.length()];
    for (uint8_t i = 0; i < targetState.length(); i++)
    {
        tempTarget->location[i] = targetState.at(i);
    }
    tempTarget->length = targetState.length();

    exist = false;
    foreach (Target *ta, target)
    {
        if (ta->ID == tempTarget->ID)
        {
            exist = true;
            ta->length = tempTarget->length;
            delete[] ta->location;
            ta->location = tempTarget->location;
            break;
        }
    }
    if (!exist)
    {
        target.append(tempTarget);
    }

}

void Mission::dispMissionItem()
{
    QString str;
    foreach (Initial *in, initial)
    {
        str = QString("Initial state of %1: (").arg(in->ID);
        for (int x = 0; x < in->length; x++)
        {
            str += (QString::number(in->location[x]) + "  ");
        }
        str += ")";
        qDebug() << str;
    }

    foreach (Target *ta, target)
    {
        str = QString("Target state of %1: (").arg(ta->ID);
        for (int x = 0; x < ta->length; x++)
        {
            str += (QString::number(ta->location[x]) + "  ");
        }
        str += ")";
        qDebug() << str;
    }
}
