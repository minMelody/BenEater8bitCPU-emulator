#include <iostream>

// Building an 8-bit breadboard computer! - Ben Eater
// https://youtube.com/playlist?list=PLowKtXNTBypGqImE405J2565dvjafglHU&feature=shared

typedef unsigned char Byte;

struct CPU {
	// registers
	Byte A, B;
	Byte Ins;	// instruction register: bits 0xF0 -> instruction, bits 0x0F -> data
};

int main()
{
	CPU cpu;

	return 0;
}
