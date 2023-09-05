#include <iostream>
#include "BE8bitCPU.h"

using namespace BE8bitCPU;

int main()
{
	RAM ram { 0x1e, 0x2f, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1c, 0x0e };

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