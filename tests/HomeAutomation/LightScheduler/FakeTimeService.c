#include "FakeTimeService.h"

static Time fakeTime;
static WakeupCallback callback;
static int period;

void TimeService_Create(void)
{
    fakeTime.minuteOfDay = -1;
    fakeTime.dayOfWeek = -1;
    callback = NULL;
    period = -1;
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

WakeupCallback FakeTimeSource_GetAlarmCallback(void)
{
    return callback;
}

int FakeTimeSource_GetAlarmPeriod(void)
{
    return period;
}

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeupCallback cb)
{
    callback = cb;
    period = seconds;
}

void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeupCallback cb)
{
    if(cb == callback && period == seconds)
    {
        callback = NULL;
        period = 0;
    }
}
