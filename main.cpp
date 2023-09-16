#include <iostream>
#include <string>
#include "BE8bitCPU.h"
#include "Assembler/Assembler.h"

using namespace BE8bitCPU;

int main(int argc, const char* argv[])
{
	std::string PROGRAM_PATH{};
	if (argc < 2)
	{
		std::cout << "Program Path: ";
		getline(std::cin, PROGRAM_PATH);
	}
	else
	{
		PROGRAM_PATH = argv[1];
	}

	// Load and assemble program
	Assembler beasm;
	RAM ram { beasm.assembleProgram(PROGRAM_PATH.c_str()) };
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