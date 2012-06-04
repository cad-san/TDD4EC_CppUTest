#ifndef D_TimeService_H
#define D_TimeService_H

typedef struct Time
{
    int minuteOfDay;
    int dayOfWeek;
} Time;

void TimeService_Create(void);
void TimeService_Destory(void);
void TimeService_GetTime(Time *time);

#endif
