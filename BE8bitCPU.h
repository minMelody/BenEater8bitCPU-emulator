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
		Byte PC;		// Program Counter
		Byte A, B, O;	// Registers
		void Reset();
		void Execute(int& cycles, RAM& ram);
	};

	struct opcodes
	{
		static constexpr Byte
			NOP = 0x00,
			LDA = 0x10,
			ADD = 0x20,
			OUT = 0xe0,
			HLT = 0xf0;
	};
}