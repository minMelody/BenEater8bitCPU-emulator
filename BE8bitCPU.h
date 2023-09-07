#pragma once
#include <cstdint>

namespace BE8bitCPU {
	typedef uint8_t Byte;

	struct RAM
	{
		static constexpr Byte MAX_SIZE { 16 };
		Byte FetchByte(Byte address, int& cycles);

		RAM(Byte prog[MAX_SIZE]) {
			for (int i = 0; i < MAX_SIZE; i++) {
				data[i] = prog[i];
			}
		}
		template<typename... Byte>
		RAM(Byte... prog) {
			int i = 0;
			for (const auto b : {prog...}) {
				data[i] = b;
				i++;
			}
		}

		// Read and write byte
		Byte& operator[] (Byte address) {
			return data[address];
		}

		private:
			Byte data[MAX_SIZE];
	};

	struct CPU {
		Byte PC;	// Program Counter
		Byte A, B;	// Registers
		bool Z, C;	// Flags
		void Reset();
		// Each instruction takes 3 cycles
		// * Normal exit returns 256
		// * A return value lower than 256 is cpu output
		unsigned int Execute(int& cycles, RAM& ram);
	};

	struct opcodes
	{
		static constexpr Byte
			NOP = 0x00,
			LDA = 0x10,
			ADD = 0x20,
			SUB = 0x30,
			STA = 0x40,
			LDI = 0x50,
			JMP = 0x60,
			JC  = 0x70,
			JZ  = 0x80,
			//  = 0x90,
			//  = 0xa0,
			//  = 0xb0,
			//  = 0xc0,
			//  = 0xd0,
			OUT = 0xe0,
			HLT = 0xf0;
	};
}