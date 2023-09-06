#include <iostream>
#include "BE8bitCPU.h"

using namespace BE8bitCPU;

int main()
{
	RAM ram { 0x53, 0x4f, 0x50, 0x2f, 0xe0, 0x63, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

	CPU cpu{};
	cpu.Reset();

	int cycles = 0;
	unsigned int out = 0x100;
	while ((out & 0xFF) < 255)
	{
		out = cpu.Execute(cycles, ram);
		if (out < 0x100) std::cout << out << '\n';
	}

	return 0;
}