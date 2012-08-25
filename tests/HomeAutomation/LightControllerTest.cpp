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
		LightDriverSpy_InstallInterface();
		LightDriverSpy_Reset();
	}
	
	void teardown()
	{
		LightController_Destroy();
	}
};
