#include "LightController.h"
#include "X10LightDriver.h"

#include <memory.h>

static LightDriver lightDrivers[MAX_LIGHTS] = { NULL };

void LightController_Create(void)
{
	memset(lightDrivers, 0, sizeof lightDrivers);
}

static void destroy(LightDriver driver)
{
	LightDriver_Destroy(driver);
}

void LightController_Destroy(void)
{
	int i;
	for (i = 0; i < MAX_LIGHTS; i++)
	{
		LightDriver driver = lightDrivers[i];
		destroy(driver);
		lightDrivers[i] = NULL;
	}
}

BOOL LightController_Add(int id, LightDriver driver)
{
	if(id < 0 && id >= MAX_LIGHTS)
		return FALSE;
	
	if(!driver)
		return FALSE;
		
	destroy(lightDrivers[id]);

	lightDrivers[id] = driver;
	return TRUE;
}

void LightController_TurnOn(int id)
{
	LightDriver_TurnOn(lightDrivers[id]);
}

void LightController_TurnOff(int id)
{
	LightDriver_TurnOff(lightDrivers[id]);
}
