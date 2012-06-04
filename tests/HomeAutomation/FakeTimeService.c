#include "FakeTimeService.h"

static Time fakeTime;

void TimeService_Create(void)
{
    fakeTime.minuteOfDay = -1;
    fakeTime.dayOfWeek = -1;
}


void TimeService_Destory(void)
{

}

void TimeService_GetTime(Time* time)
{
    time->dayOfWeek = fakeTime.dayOfWeek;
    time->minuteOfDay = fakeTime.minuteOfDay;
}


void FakeTimeService_SetMinute(int minute)
{
    fakeTime.minuteOfDay = minute;
}

void FakeTimeService_SetDay(Day day)
{
    fakeTime.dayOfWeek = day;
}
