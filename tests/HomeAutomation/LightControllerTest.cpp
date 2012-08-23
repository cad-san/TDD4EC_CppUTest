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
	}
	
	void teardown()
	{
		LightController_Destroy();
	}
};
