#pragma once

namespace BE8bitCPU
{
	struct Assembler
	{
		uint8_t* assembleProgram(const char* filePath);
		void interpretLine(std::string line, uint8_t prog[RAM::MAX_SIZE], unsigned int& counter);
	};

}