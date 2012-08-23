#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LightDriverSpy.h"
}

TEST_GROUP(LightDriverSpy)
{
	LightDriver lightDriverSpy;
	
	void setup()
	{
		LightDriverSpy_Reset();
		lightDriverSpy = LightDriverSpy_Create(1);
	}
	
	void teardown()
	{
		LightDriverSpy_Destroy(lightDriverSpy);
	}
};

TEST(LightDriverSpy, On)
{
	LightDriverSpy_TurnOn(lightDriverSpy);
	LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetState(1));
}
