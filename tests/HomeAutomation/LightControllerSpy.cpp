#include "LightControllerSpy.h"

static int lastId;
static int lastState;

void LightController_Create(void)
{
    lastId = LIGHT_ID_UNKNOWN;
    lastState = LIGHT_STATE_UNKNOWN;
}

void LightController_Destory(void)
{
}
