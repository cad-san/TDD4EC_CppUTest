#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LightScheduler.h"
#include "LightControllerSpy.h"
#include "FakeTimeService.h"
}

TEST_GROUP(LightScheduler)
{
    void setup()
    {
        LightController_Create();
        LightScheduler_Create();
    }

    void teardown()
    {
        LightController_Destroy();
        LightScheduler_Destroy();
    }

    void setTimeTo(Day day, int minuteOfDay)
    {
        FakeTimeService_SetDay(day);
        FakeTimeService_SetMinute(minuteOfDay);
    }

    void checkLightState(int id, int level)
    {
        LONGS_EQUAL(id, LightControllerSpy_GetLastId());
        LONGS_EQUAL(level, LightControllerSpy_GetLastState());
    }
};

TEST(LightScheduler, NoScheduleNothingHappens)
{
    setTimeTo(MONDAY, 100);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnEverydayNotTimeYet)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1199);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleOnEverydayItsTime)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleOffEverydayItsTime)
{
    LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_OFF);
}

TEST(LightScheduler, ScheduleTuesDayButItsMonday)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleTuesDayAndItsTuesday)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(TUESDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekEndItsFriday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(FRIDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST(LightScheduler, ScheduleWeekEndItsSaturday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SATUADAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekEndItsSunday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SUNDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
}

TEST(LightScheduler, ScheduleWeekEndItsMonday)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(TUESDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

TEST_GROUP(LightSchedulerInitAndCleanup)
{
};

TEST(LightSchedulerInitAndCleanup, CreateStartsOneMinuteAlarm)
{
    LightScheduler_Create();
    POINTERS_EQUAL((void *)LightScheduler_Wakeup,
                   (void *)FakeTimeSource_GetAlarmCallback());
    LONGS_EQUAL(60, FakeTimeSource_GetAlarmPeriod());
    LightScheduler_Destroy();
}

TEST(LightSchedulerInitAndCleanup, DestroyCancelsOneMinuteAlarm)
{
    LightScheduler_Create();
    LightScheduler_Destroy();
    POINTERS_EQUAL(NULL, (void *)FakeTimeSource_GetAlarmCallback());
}
