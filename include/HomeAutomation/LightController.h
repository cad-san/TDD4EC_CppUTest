#ifndef D_LightController_H
#define D_LightController_H

#include "LightDriver.h"

enum { MAX_LIGHTS = 32 };

#ifndef BOOL
#define BOOL int
#endif

void LightController_Create(void);
void LightController_Destroy(void);
BOOL LightController_Add(int id, LightDriver);
void LightController_TurnOn(int id);
void LightController_TurnOff(int id);

#endif
