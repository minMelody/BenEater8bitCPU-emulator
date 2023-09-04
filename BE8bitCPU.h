#pragma once

namespace BE8bitCPU {
	typedef unsigned char Byte;

	struct RAM
	{
		static constexpr Byte MAX_SIZE { 16 };

		// Read and write byte
		Byte& operator[] (Byte address) {
			return data[address];
		}

		private:
			Byte data[MAX_SIZE];
	};

	struct CPU {

		Byte PC;		// Program Counter
		Byte A, B, OUT;	// Registers
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