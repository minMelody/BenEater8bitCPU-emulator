#include <iostream>
#include "BE8bitCPU.h"

using namespace BE8bitCPU;

int main()
{
	RAM ram { 0x1e, 0x3c, 0x76, 0x1d, 0xe0, 0xf0, 0x4e, 0x1d, 0x2f, 0x4d, 0x60, 0xff, 0x01, 0x00, 0x07, 0x08 };

	CPU cpu{};
	cpu.Reset();

	int cycles = INT_MAX;
	unsigned int out = 0x100;
	while (cycles > 0)
	{
		out = cpu.Execute(cycles, ram);
		if (out < 0x100) std::cout << out << '\n';
	}

	return 0;
}