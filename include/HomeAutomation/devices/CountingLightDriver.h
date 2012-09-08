#ifndef D_CountingLightDriver_H
#define D_CountingLightDriver_H

#include "LightDriver.h"
#include "LightDriverPrivate.h"

/* inherited */
LightDriver CountingLightDriver_Create(int id);
void CountingLightDriver_Destroy(LightDriver base);
void CountingLightDriver_TurnOn(LightDriver base);
void CountingLightDriver_TurnOff(LightDriver base);

int CountingLightDriver_GetCallCount(LightDriver base);

#endif
