// Building an 8-bit breadboard computer! - Ben Eater
// https://youtube.com/playlist?list=PLowKtXNTBypGqImE405J2565dvjafglHU&feature=shared

#include "BE8bitCPU.h"

void BE8bitCPU::CPU::Reset()
{
	PC = A = B = 0;
	Z = C = HALT = false;
}

unsigned int Sum(uint8_t A, uint8_t B, bool& C, bool& Z) {
	unsigned int sum = A + B;
	C = (sum > 0xFF);
	Z = (sum & 0xFF) == 0;
	return sum;
}

void BE8bitCPU::CPU::Execute(RAM& ram)
{
	// The 4 higher bits represent the opcode
	// While the 4 lowest bits represent the data (memory address, load immediate value, etc.)
	IR = ram[PC];

	// Increment the program counter
	// The way Ben Eater built his program counter it wraps around on overflow
	PC = (PC + 1) % ram.MAX_SIZE;

	switch (IR & 0xf0)
	{
		case opcodes::NOP:
			break;
		case opcodes::LDA:
			A = ram[IR & 0x0f];
			break;
		case opcodes::ADD:
			B = ram[IR & 0x0f];
			A = Sum(A, B, C, Z);
			break;
		case opcodes::SUB:
			B = ram[IR & 0x0f];
			A = Sum(A, -B, C, Z);
			break;
		case opcodes::STA:
			ram[IR & 0x0f] = A;
			break;
		case opcodes::LDI:
			A = IR & 0x0f;
			break;
		case opcodes::JMP:
			PC = IR & 0x0f;
			break;
		case opcodes::JC:
			PC = C ? (IR & 0x0f) : PC;
			break;
		case opcodes::JZ:
			PC = Z ? (IR & 0x0f) : PC;
			break;
		case opcodes::OUT:
			OUT = A;
			return;
		case opcodes::HLT:
			HALT = true;
			break;
		default:
			OUT = UINT16_MAX; // Invalid instruction code
			HALT = true;
			return;
	}

	OUT = 256; // Normal exit code
}
