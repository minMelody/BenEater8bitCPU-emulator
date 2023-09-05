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

		// Read and write byte
		Byte& operator[] (Byte address) {
			return data[address];
		}

		private:
			Byte data[MAX_SIZE];
	};

	struct CPU {
		Byte PC;		// Program Counter
		Byte A, B, O;	// Registers
		void Reset();
		void Execute(int& cycles, RAM& ram);
	};

	struct opcodes
	{
		static constexpr Byte
			LDA = 0x00,
			ADD = 0x10,
			OUT = 0x20,
			HLT = 0xf0;
	};
}