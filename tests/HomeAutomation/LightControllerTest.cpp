#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LightController.h"
#include "LightDriverSpy.h"
}

TEST_GROUP(LightController)
{
	LightDriver spy;
	
	void setup()
	{
		LightController_Create();
		LightDriverSpy_AddSpiesToController();
		LightDriverSpy_Reset();
	}
	
	void teardown()
	{
		LightController_Destroy();
	}
};

TEST(LightController, CreateDestroy)
{
}

TEST(LightController, TurnOn)
{
	LightController_TurnOn(7);
	LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetState(7));
}

TEST(LightController, TurnOff)
{
    LightController_TurnOff(1);
    LONGS_EQUAL(LIGHT_OFF, LightDriverSpy_GetState(1));
}
