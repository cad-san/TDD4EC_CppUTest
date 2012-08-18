#ifndef D_TimeService_H
#define D_TimeService_H

typedef struct Time
{
    int minuteOfDay;
    int dayOfWeek;
} Time;

typedef enum {
    NONE = -1, EVERYDAY = 10, WEEKDAY, WEEKEND,
    SUNDAY = 1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATUADAY
} Day;

void TimeService_Create(void);
void TimeService_Destory(void);
void TimeService_GetTime(Time *time);

typedef void (*WakeupCallback)(void);

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeupCallback cb);
void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeupCallback cb);
#endif
