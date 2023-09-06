// Building an 8-bit breadboard computer! - Ben Eater
// https://youtube.com/playlist?list=PLowKtXNTBypGqImE405J2565dvjafglHU&feature=shared

#include "BE8bitCPU.h"

BE8bitCPU::Byte BE8bitCPU::RAM::FetchByte(Byte address, int& cycles)
{
	cycles--;
	return data[address];
}

void BE8bitCPU::CPU::Reset()
{
	PC = A = B = 0;
}

unsigned int BE8bitCPU::CPU::Execute(int& cycles, RAM& ram)
{
	Byte ins = ram.FetchByte(PC, cycles);	// Instructions: bits 7-4 -> instruction, bits 3-0 -> data
	PC = (PC + 1) % ram.MAX_SIZE;
	cycles--;

	switch (ins & 0xf0)
	{
		case opcodes::NOP:
			cycles -= 3;	// Do nothing for 3 cycles
			break;
		case opcodes::LDA:
			A = ram.FetchByte(ins & 0x0f, cycles);
			cycles--;
			cycles--;		// Extra cycle
			break;
		case opcodes::ADD:
			B = ram.FetchByte(ins & 0x0f, cycles);
			cycles--;
			A += B;
			cycles--;
			break;
		case opcodes::SUB:
			B = ram.FetchByte(ins & 0x0f, cycles);
			cycles--;
			A -= B;
			cycles--;
			break;
		case opcodes::STA:
			ram[ins & 0x0f] = A;
			cycles -= 2;
			cycles--;		// Extra cycle
			break;
		case opcodes::LDI:
			A = ins & 0x0f;
			cycles--;
			cycles -= 2;	// Extra cycles
			break;
		case opcodes::JMP:
			PC = ins & 0x0f;
			cycles--;
			cycles -= 2;	// Extra cycles
			break;
		case opcodes::OUT:
			cycles -= 3;
			return A;
			break;
		case opcodes::HLT:
			cycles = 0;		// Stops clock
			break;
		default:
			break;
	}

	return 0x100;
}
