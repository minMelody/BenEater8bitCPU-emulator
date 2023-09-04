// Building an 8-bit breadboard computer! - Ben Eater
// https://youtube.com/playlist?list=PLowKtXNTBypGqImE405J2565dvjafglHU&feature=shared

#include "BE8bitCPU.h"

void BE8bitCPU::CPU::Execute(int& cycles, RAM& ram)
{
	PC %= ram.MAX_SIZE;

	Byte ins = ram[PC];	// Instructions: bits 7-4 -> instruction, bits 3-0 -> data
	cycles -= 2;

	switch (ins & 0xf0)
	{
		case opcodes::LDA:
			A = ram[ins & 0x0f];
			PC++;
			cycles -= 3;
			break;
		case opcodes::ADD:
			A += ram[ins & 0x0f];
			PC++;
			cycles -= 3;
			break;
		case opcodes::OUT:
			OUT = A;
			PC++;
			cycles -= 3;
			break;
		case opcodes::HLT:
			cycles = 0;
			break;
		default:
			break;
		}
}
