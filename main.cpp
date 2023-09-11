#include <iostream>
#include <fstream>
#include "BE8bitCPU.h"

using namespace BE8bitCPU;


#if defined _DEBUG
#define PROG "debug.bin"
#else
#define PROG argv[1]
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
	RAM ram { loadProgram(PROG) };

	CPU cpu;
	cpu.Reset();

	// Execute until the HALT flag is set
	while (!cpu.HALT)
	{
		cpu.Execute(ram);
		if (cpu.OUT < 256) std::cout << cpu.OUT << '\n';
		else if (cpu.OUT == UINT16_MAX) printf("Invalid instruction: %02x \n", cpu.IR);
	}

	return 0;
}