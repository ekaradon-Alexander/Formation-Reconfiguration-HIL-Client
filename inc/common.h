#ifndef COMMON_H
#define COMMON_H

#include <inttypes.h>
#include <qstring.h>

#define DEFAULT_CLIENT_PORT 12345

#define TIME_STAMP ("[" + QDateTime::currentDateTime().toString("mm:ss") + "] ")

#define MAX_STATE_COUNT 6
#define MAX_CONTROL_COUNT 4

enum TASK_STATUS
{
    NO_MODEL,
    NO_DEVICE,
    NO_MISSION,
    READY,
    SIMULATION,
    STOP,
};

typedef struct _Setting
{
    uint16_t clientPort;
    QString clientIP;
    uint16_t plottingTime;
    uint16_t controlTime;
} Setting;

extern TASK_STATUS g_status;
extern Setting g_setting;


#endif // COMMON_H
