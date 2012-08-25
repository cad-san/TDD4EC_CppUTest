#ifndef D_LightDriverPrivate_H
#define D_LightDriverPrivate_H

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

typedef struct LightDriverInterfaceStruct
{
	void (*TurnOn)(LightDriver);
	void (*TurnOff)(LightDriver);
	void (*Destroy)(LightDriver);
} LightDriverInterfaceStruct;

#endif
