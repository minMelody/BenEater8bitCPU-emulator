#include <iostream>
#include "BE8bitCPU.h"

using namespace BE8bitCPU;

int main()
{
	RAM ram { 0x1f, 0x2e, 0x3d, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x06, 0x05 };

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