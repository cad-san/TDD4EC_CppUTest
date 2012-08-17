#ifndef D_LightScheduler_H
#define D_LightScheduler_H

#include "TimeService.h"

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);
void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay);
void LightScheduler_Wakeup(void);
#endif
