#ifndef CONTROLLERCOMMUNICATION_H
#define CONTROLLERCOMMUNICATION_H

#include <inttypes.h>
#include <common.h>

enum MESSAGE_TYPE
{
    CONNECTION,
    CONTROL,
};

/**
 * @brief data from controller to client
 */
union ControllerToClientPayLoad
{
#ifdef __cplusplus
    ControllerToClientPayLoad() { memset(this, 0, sizeof(*this)); }
    ~ControllerToClientPayLoad() {}
#endif

    struct
    {
        uint8_t valid;      // result of controller validation, 0x01 for success
    } connectionResult;

    struct
    {
        uint8_t nControllerControl;     // number of controls
        float controls[MAX_CONTROL_COUNT];
    } controlResult;
};

typedef struct _ControllerToClient
{
    enum MESSAGE_TYPE type;
    uint8_t ID;
    union ControllerToClientPayLoad payLoad;
} ControllerToClient;

/**
 * @brief data from client to controller
 */
union ClientToControllerPayLoad
{
#ifdef __cplusplus
    ClientToControllerPayLoad() { memset(this, 0, sizeof(*this)); }
    ~ClientToControllerPayLoad() {}
#endif

    struct
    {
        uint32_t clientIP;      // connection result is sent to this IP
        uint16_t clientPort;    // connection result is sent to this port
        uint8_t modelID;          // model of the device
        uint8_t nModelState;         // number of state
        uint8_t nModelControl;       // number of control
        // number of state in the CONTROLLER should be less or equal to nModelState
    } connectionRequest;

    struct
    {
        uint8_t nModelState;
        float states[MAX_STATE_COUNT];
    } controlRequest;
};

typedef struct ClientToController
{
    enum MESSAGE_TYPE type;
    uint8_t ID;
    union ClientToControllerPayLoad payLoad;
} ClientToController;


#endif // CONTROLLERCOMMUNICATION_H
