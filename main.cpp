#include <iostream>
#include <fstream>
#include "BE8bitCPU.h"

using namespace BE8bitCPU;

#if defined _DEBUG
#define PROGRAM "debug.bin"
#else
#define PROGRAM argv[1]
#endif

uint8_t* loadProgram(const char* filePath) {
	std::ifstream f(filePath);
	f.seekg(0, std::ios_base::end);
	unsigned long size = f.tellg();
	f.seekg(0, std::ios_base::beg);
	if (f.is_open()) {
		uint8_t* buffer = (uint8_t*)malloc((size+1) * sizeof(uint8_t));
		f.read((char*)buffer, size);
		f.close();
		return (uint8_t*)buffer;
	}
	else std::cout << "Unable to open file path \n" << filePath;

	return (uint8_t*)"";
}

int main()
{
	RAM ram { loadProgram(PROGRAM) };

	CPU cpu;
	cpu.Reset();

	// Execute until the HALT flag is set
	while (!cpu.HALT)
	{
		cpu.Execute(ram);
		if (cpu.OE) printf("%d \n", cpu.OUT);
		if (cpu.IIE) printf("Invalid instruction: %02x at address 0x%02x \n", cpu.IR, cpu.PC - 1);
	}

	return 0;
}