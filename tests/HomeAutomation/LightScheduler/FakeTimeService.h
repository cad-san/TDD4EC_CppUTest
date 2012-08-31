#ifndef D_FakeTimeService_H
#define D_FakeTimeService_H

#include "TimeService.h"

enum {TIME_UNKNOWN = -1};

void FakeTimeService_SetMinute(int minute);
void FakeTimeService_SetDay(Day day);

WakeupCallback FakeTimeSource_GetAlarmCallback(void);
int FakeTimeSource_GetAlarmPeriod(void);

#endif
