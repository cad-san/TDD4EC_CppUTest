#include "LightDriver.h"
#include "LightDriverPrivate.h"
#include "common.h"

static BOOL isValid(LightDriver self)
{
	return self && self->vtable;
}

LightDriverStruct LightDriver_Create(LightDriverInterface interface, const char* type, int id)
{
	LightDriverStruct self;
	self.vtable = interface;
	self.id = id;
	self.type = type;
	return self;
}

void LightDriver_Destroy(LightDriver self)
{
	if(isValid(self))
		self->vtable->Destroy(self);
}

void LightDriver_TurnOn(LightDriver self)
{
	if(isValid(self))
		self->vtable->TurnOn(self);
}

void LightDriver_TurnOff(LightDriver self)
{
	if(isValid(self))
		self->vtable->TurnOff(self);
}
