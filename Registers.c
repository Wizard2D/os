#include "Registers.h"

struct Registers current = { 0 };

void SaveConInt();

void SaveConInfo(struct Registers *reg)
{
	memcpy(&current, reg, sizeof(struct Registers));
}

//extern void load_current(void);

struct Registers GetRegisters()
{
	//load_current();
	return current;
}