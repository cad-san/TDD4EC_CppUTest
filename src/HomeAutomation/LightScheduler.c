#include "LightScheduler.h"
#include "LightController.h"

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

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

static ScheduledLightEvent scheduledEvent;

void LightScheduler_Create(void)
{
    scheduledEvent.id = UNUSED;
}

void LightScheduler_Destroy(void)
{
}

static void scheduleEvent(int id, Day day, int minuteOfDay, int event)
{
    scheduledEvent.id = id;
    scheduledEvent.day = day;
    scheduledEvent.minuteOfDay = minuteOfDay;
    scheduledEvent.event = event;
}

void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
    scheduleEvent(id, day, minuteOfDay, TURN_ON);
}

void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
    scheduleEvent(id, day, minuteOfDay, TURN_OFF);
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
        LightController_On(lightEvent->id);
    else if (lightEvent->event == TURN_OFF)
        LightController_Off(lightEvent->id);   
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
    Time time;
    TimeService_GetTime(&time);

    processEventDueNow(&time, &scheduledEvent);
}
