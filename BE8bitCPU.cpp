#include <iostream>

// Building an 8-bit breadboard computer! - Ben Eater
// https://youtube.com/playlist?list=PLowKtXNTBypGqImE405J2565dvjafglHU&feature=shared

typedef unsigned char Byte;

struct RAM
{
	static constexpr Byte MAX_SIZE = 16;
	Byte data[MAX_SIZE];

	// read byte
	Byte operator[] (Byte address) const {
		return data[address];
	}
	// write byte
	Byte& operator[] (Byte address) {
		return data[address];
	}
};

struct CPU {
	// registers
	Byte A, B;
	Byte Ins;	// instruction register: bits 0xF0 -> instruction, bits 0x0F -> data
};

int main()
{
	RAM ram;
	CPU cpu;

	return 0;
}
