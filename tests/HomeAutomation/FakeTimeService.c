#include "FakeTimeService.h"

void TimeService_Create(void)
{

}


void TimeService_Destory(void)
{

}

void TimeService_GetTime(Time* time)
{
    time->dayOfWeek = TIME_UNKNOWN;
    time->minuteOfDay = TIME_UNKNOWN;
}
