#pragma once
#include <cstdint>

namespace BE8bitCPU {
	struct RAM {
		public:
			static constexpr uint8_t MAX_SIZE { 16 };

			// Constructor loads a program in memory
			RAM(uint8_t prog[MAX_SIZE]) {
				for (int i = 0; i < MAX_SIZE; i++) {
					data[i] = prog[i];
				}
			}
			template<typename... uint8_t>
			// Constructor loads a program in memory
			RAM(uint8_t... prog) {
				int i = 0;
				for (const auto b : { prog... }) {
					data[i] = b;
					i++;
				}
			}
			~RAM() {}

			// Read and write byte
			uint8_t& operator[] (uint8_t address) {
				return data[address];
			}

		private:
			uint8_t data[MAX_SIZE];
	};

	struct CPU {
		public:
			uint8_t PC;			// Program Counter
			uint8_t IR;			// Instruction Register
			uint8_t A, B, OUT;	// Registers

			bool Z, C;	// CPU Flags
			bool HALT;
			bool OE;	// Output Enable
			bool IIE;	// Invalid Instruction Exception

			void Reset();
			// A return value of zero (0) is normal return.
			// See EmulationFlags for other return value.
			void Execute(RAM& ram);
	};

	struct opcodes {
		public:
			static constexpr uint8_t
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