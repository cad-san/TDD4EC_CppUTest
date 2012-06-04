#include "CppUTest/TestHarness.h"

extern "C"
{
#include "FakeTimeService.h"
}

TEST_GROUP(FakeTimeService)
{
    void setup()
    {
        TimeService_Create();
    }

    void teardown()
    {
        TimeService_Destory();
    }
};

TEST(FakeTimeService, Create)
{
    Time time;
    TimeService_GetTime(&time);

    LONGS_EQUAL(TIME_UNKNOWN, time.minuteOfDay);
    LONGS_EQUAL(TIME_UNKNOWN, time.dayOfWeek);
}

TEST(FakeTimeService, Set)
{
    Time time;
    FakeTimeService_SetMinute(42);
    FakeTimeService_SetDay(SATUADAY);

    TimeService_GetTime(&time);

    LONGS_EQUAL(42, time.minuteOfDay);
    LONGS_EQUAL(SATUADAY, time.dayOfWeek);
}
