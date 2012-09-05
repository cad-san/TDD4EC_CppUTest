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

#define NONSENSE_POINTER (LightDriver)~0
static LightDriver savedDriver = NONSENSE_POINTER;
static void shouldNotBeCalled(LightDriver self) { savedDriver = self; }

LightDriverInterfaceStruct interface =
{
	shouldNotBeCalled,
	shouldNotBeCalled,
	shouldNotBeCalled
};

LightDriverStruct testDriver =
{
	&interface,
	"TestLightDriver",
	13
};

TEST(LightDriver, NullDriverDoesNotCrash)
{
	LightDriver_TurnOn(NULL);
	LightDriver_TurnOff(NULL);
	LightDriver_Destroy(NULL);
	POINTERS_EQUAL(NONSENSE_POINTER, savedDriver);
}
