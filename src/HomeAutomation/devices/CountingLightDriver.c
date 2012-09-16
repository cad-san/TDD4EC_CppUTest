#include "CountingLightDriver.h"

typedef struct CountingLightDriverStruct* CountingLightDriver;

typedef struct CountingLightDriverStruct
{
	LightDriverStruct base;
	int counter;
} CountingLightDriverStruct;

void CountingLightDriver_Destroy(LightDriver base);
void CountingLightDriver_TurnOn(LightDriver base);
void CountingLightDriver_TurnOff(LightDriver base);

static LightDriverInterfaceStruct interface = {
	CountingLightDriver_TurnOn,
	CountingLightDriver_TurnOff,
	CountingLightDriver_Destroy
};

LightDriver CountingLightDriver_Create(int id)
{
	CountingLightDriver self = calloc(1, sizeof(CountingLightDriverStruct));
	self->base = LightDriver_Create(&interface, "CountingLightDriver", id);
	self->counter = 0;
	return (LightDriver)self;
}
void CountingLightDriver_Destroy(LightDriver base)
{
	CountingLightDriver self = (CountingLightDriver)base;
	free(self);
}

static void count(LightDriver base)
{
	CountingLightDriver self = (CountingLightDriver)base;
	self->counter++;
}

void CountingLightDriver_TurnOn(LightDriver base)
{
	count(base);
}

void CountingLightDriver_TurnOff(LightDriver base)
{
	count(base);
}

int CountingLightDriver_GetCallCount(LightDriver base)
{
	CountingLightDriver self = (CountingLightDriver)base;
	return self->counter;
}
