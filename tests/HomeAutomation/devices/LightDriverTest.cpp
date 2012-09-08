#include "CppUTest/TestHarness.h"

extern "C"
{
#include "LightDriverSpy.h"
}

TEST_GROUP(LightDriver)
{
	void setup()
	{
	}
	
	void teardown()
	{
	}
};

static void null(LightDriver self) {}

static LightDriverInterfaceStruct interface =
{
	null,
	null,
	null
};

static LightDriverStruct testDriver =
{
	&interface,
	"TestLightDriver",
	13
};

static LightDriverStruct nullInterfaceDriver =
{
	NULL,
	"TestLightDriver",
	13
};

TEST(LightDriver, NullDriverDoesNoHarm)
{
	LightDriver_TurnOn(NULL);
	LightDriver_TurnOff(NULL);
	LightDriver_Destroy(NULL);
}

TEST(LightDriver, NullInterfaceDoesNoHarm)
{
	LightDriver_TurnOn(&nullInterfaceDriver);
	LightDriver_TurnOff(&nullInterfaceDriver);
	LightDriver_Destroy(&nullInterfaceDriver);
}

TEST(LightDriver, Accessors)
{
	LONGS_EQUAL(13, LightDriver_GetId(&testDriver));
	STRCMP_EQUAL("TestLightDriver", LightDriver_GetType(&testDriver));
}
