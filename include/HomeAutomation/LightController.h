#ifndef D_LightController_H
#define D_LightController_H

#include "LightDriver.h"
#include "common.h"

enum { MAX_LIGHTS = 32 };

void LightController_Create(void);
void LightController_Destroy(void);
BOOL LightController_Add(int id, LightDriver);
void LightController_TurnOn(int id);
void LightController_TurnOff(int id);

#endif
