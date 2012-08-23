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
	if (!driver)
		return;
	
	switch (driver->type)
	{
	case X10:
		X10LightDriver_Destroy(driver);
		break;
	default:
		/* now what? */
		break;
	}
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

void LightController_TurnOn(int id)
{
	LightDriver driver = lightDrivers[id];
	if (NULL == driver)
		return;
		
	switch (driver->type)
	{
	case X10:
		X10LightDriver_TurnOn(driver);
	default:
		/* now what? */
		break;
	}
}

void LightController_TurnOff(int id)
{
	LightDriver driver = lightDrivers[id];
	if (NULL == driver)
		return;
		
	switch (driver->type)
	{
	case X10:
		X10LightDriver_TurnOff(driver);
	default:
		/* now what? */
		break;
	}
}

