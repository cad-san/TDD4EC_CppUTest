#include "LightScheduler.h"
#include "LightController.h"
#include "common.h"

enum
{
    UNUSED = -1,
    TURN_OFF, TURN_ON,
    MAX_EVENTS = 128
};

typedef struct
{
    int id;
    int day;
    int minuteOfDay;
    int event;
} ScheduledLightEvent;

static ScheduledLightEvent scheduledEvents[MAX_EVENTS];

void LightScheduler_Create(void)
{
    int i;

    for(i = 0; i < MAX_EVENTS; i++)
        scheduledEvents[i].id = UNUSED;

    TimeService_SetPeriodicAlarmInSeconds(60,
            LightScheduler_Wakeup);
}

void LightScheduler_Destroy(void)
{
    TimeService_CancelPeriodicAlarmInSeconds(60,
            LightScheduler_Wakeup);
}

static int scheduleEvent(int id, Day day, int minuteOfDay, int event)
{
    int i;

    if(id < 0 || id >= MAX_LIGHTS)
        return LS_ID_OUT_OF_BOUNDS;

    for(i = 0; i < MAX_EVENTS; i++)
    {
        if (scheduledEvents[i].id == UNUSED)
        {
            scheduledEvents[i].day = day;
            scheduledEvents[i].minuteOfDay = minuteOfDay;
            scheduledEvents[i].event = event;
            scheduledEvents[i].id = id;
            return LS_OK;
        }
    }
    return LS_TOO_MANY_EVENTS;
}

int LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
    return scheduleEvent(id, day, minuteOfDay, TURN_ON);
}

int LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
    return scheduleEvent(id, day, minuteOfDay, TURN_OFF);
}

void LightScheduler_ScheduleRemove(int id, Day day, int minuteOfDay)
{
    int i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if ( scheduledEvents[i].id == id &&
             scheduledEvents[i].day == day &&
             scheduledEvents[i].minuteOfDay == minuteOfDay)
        {
            scheduledEvents[i].id = UNUSED;
        }
    }
}

static int doesLightRespondToday(Time* time, int reactionDay)
{
    int today = time->dayOfWeek;

    if (reactionDay == EVERYDAY)
        return TRUE;
    if (reactionDay == today)
        return TRUE;
    if (reactionDay == WEEKEND && (SATUADAY == today || SUNDAY == today))
        return TRUE;
    if (reactionDay == WEEKDAY && today >= MONDAY && today <= FRIDAY)
        return TRUE;
    return FALSE;
}

static void operateLight(ScheduledLightEvent* lightEvent)
{
    if (lightEvent->event == TURN_ON)
        LightController_TurnOn(lightEvent->id);
    else if (lightEvent->event == TURN_OFF)
        LightController_TurnOff(lightEvent->id);
}

static void processEventDueNow(Time* time, ScheduledLightEvent* lightEvent)
{
    if (lightEvent->id == UNUSED)
        return;
    if (!doesLightRespondToday(time, lightEvent->day))
        return;
    if (lightEvent->minuteOfDay != time->minuteOfDay)
        return;

    operateLight(lightEvent);
}

void LightScheduler_Wakeup(void)
{
    int i;
    Time time;
    TimeService_GetTime(&time);

    for (i = 0; i < MAX_EVENTS; i++)
    {
        processEventDueNow(&time, &scheduledEvents[i]);
    }
}
