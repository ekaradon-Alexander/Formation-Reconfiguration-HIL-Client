#ifndef COMMON_H
#define COMMON_H

#include <inttypes.h>
#include <qstring.h>

#define DEFAULT_CLIENT_PORT 12345

#define TIME_STAMP ("[" + QDateTime::currentDateTime().toString("mm:ss") + "] ")

#define MAX_CONTROL_NUMBER      3
#define MAX_STATE_NUMBER        6
#define LOC_STATE_NUMBER        3       // location state number = 3 (x, y, z)
#define MAX_DEVICE_NUMBER       10

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
    QString outputDir;
} Setting;

extern TASK_STATUS g_status;
extern Setting g_setting;


#endif // COMMON_H
