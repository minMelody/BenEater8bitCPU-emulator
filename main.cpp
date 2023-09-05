#include <iostream>
#include "BE8bitCPU.h"

using namespace BE8bitCPU;

int main()
{
	Byte prog[RAM::MAX_SIZE] = { 0x0e, 0x1f, 0x20, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1c, 0x0e };
	RAM ram{ prog };

	CPU cpu{};
	cpu.Reset();

	int cycles = 16;
	while(cycles > 0)
	{
		cpu.Execute(cycles, ram);
	}
	std::cout << (unsigned int)cpu.O;

	return 0;
}