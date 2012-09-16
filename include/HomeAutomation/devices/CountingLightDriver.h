#ifndef D_CountingLightDriver_H
#define D_CountingLightDriver_H

#include "LightDriver.h"
#include "LightDriverPrivate.h"

/* inherited */
LightDriver CountingLightDriver_Create(int id);

int CountingLightDriver_GetCallCount(LightDriver base);

#endif
