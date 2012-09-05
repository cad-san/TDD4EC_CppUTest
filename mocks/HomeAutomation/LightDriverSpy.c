#include "LightDriverSpy.h"
#include "LightController.h"
#include <stdlib.h>

typedef struct LightDriverSpyStruct* LightDriverSpy;
typedef struct LightDriverSpyStruct
{
	LightDriverStruct base;
} LightDriverSpyStruct;

static int states[MAX_LIGHTS];
static int lastId;
static int lastState;

static LightDriverInterfaceStruct interface = {
	LightDriverSpy_TurnOn,
	LightDriverSpy_TurnOff,
	LightDriverSpy_Destroy
};

static int isIdInRange(int id)
{
    return id >= 0 && id <= MAX_LIGHTS - 1;
}

LightDriver LightDriverSpy_Create(int id)
{
	LightDriverSpy self;
	if (!isIdInRange(id))
		return NULL;

	self = calloc(1, sizeof(LightDriverSpyStruct));
    if (self == NULL)
    	return NULL;

	self->base = LightDriver_Create(&interface, "TestLightDriver", id);
	return (LightDriver)self;
}

void LightDriverSpy_Destroy(LightDriver super)
{
    LightDriverSpy self = (LightDriverSpy)super;
    if (self == NULL)
    	return;
    states[self->base.id] = LIGHT_STATE_UNKNOWN;
    free(self);
}

static void save(int id, int state)
{
	states[id] = state;
	lastId = id;
	lastState = state;
}

void LightDriverSpy_TurnOn(LightDriver super)
{
    LightDriverSpy self = (LightDriverSpy)super;
    if (self == NULL)
    	return;
    save(self->base.id, LIGHT_ON);
}

void LightDriverSpy_TurnOff(LightDriver super)
{
    LightDriverSpy self = (LightDriverSpy)super;
    if (self == NULL)
    	return;
    save(self->base.id, LIGHT_OFF);
}

void LightDriverSpy_Reset(void)
{
	int i;
	for (i = 0; i < MAX_LIGHTS; i++)
	{
		save(i, LIGHT_STATE_UNKNOWN);
	}
}

int LightDriverSpy_GetState(int id)
{
	if (!isIdInRange(id))
		return LIGHT_ID_UNKNOWN;
	return states[id];
}

void LightDriverSpy_AddSpiesToController(void)
{
	int i;
	for(i = 0; i < MAX_LIGHTS;i++)
	{
		LightDriver driver = (LightDriver) LightDriverSpy_Create(i);
		LightController_Add(i, driver);
	}
}
