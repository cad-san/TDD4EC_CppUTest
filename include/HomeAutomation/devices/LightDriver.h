#ifndef D_LightDriver_H
#define D_LightDriver_H

typedef struct LightDriverStruct* LightDriver;

typedef enum LightDriverType
{
	TestLightDriver,
	X10,
	AcmeWireless,
	MemoryMapped
} LightDriverType;

typedef struct LightDriverStruct
{
	LightDriverType type;
	int id;
} LightDriverStruct;

#endif
