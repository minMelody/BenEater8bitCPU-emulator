#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "../BE8bitCPU.h"
#include "Assembler.h"

std::vector<std::string> split(std::string str, char delimiter)
{
    std::vector<std::string> vec;
    size_t pos = 0;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        std::string subst = str.substr(0, pos);
        if (subst.length() > 0) vec.push_back(subst);
        str.erase(0, pos + 1);
    }
    if (str.length() > 0) vec.push_back(str);
    return vec;
}

// Converts decimal, hexadecimal and binary numbers with prefixes to an 8 bits unsigned integer.
uint8_t stobyte(std::string str) {
    int base = 10;
    if (strncmp(str.c_str(), "0x", 2) == 0 || strncmp(str.c_str(), "0X", 2) == 0) return stoi(str, nullptr, 16);
    if (strncmp(str.c_str(), "0b", 2) == 0 || strncmp(str.c_str(), "0B", 2) == 0) return stoi(str.substr(2), nullptr, 2);
    return stoi(str);
}

void writeValues(uint8_t start_adr, std::vector<std::string> values, unsigned int& counter, uint8_t prog[])
{
    for (int i = 0; i < values.size(); i++) {
        if (start_adr + i >= BE8bitCPU::RAM::MAX_SIZE) break;
        uint8_t value = stobyte(values[i]);
        prog[start_adr + i] = value;
        counter += (start_adr + i == counter);
    }
}

void writeInstruction(uint8_t opcode, uint8_t data, unsigned int& counter, uint8_t prog[])
{
    prog[counter] = opcode + (data & 0x0f);
    counter++;
}

uint8_t* BE8bitCPU::Assembler::assembleProgram(const char* filePath)
{
    std::ifstream f(filePath);
    if (f.is_open()) {
        // Initialize program with a bunch of no-ops
        // Prevents gaps in addresses to cause undefined behavior
        uint8_t prog[RAM::MAX_SIZE]{};
        for (int i = 0; i < RAM::MAX_SIZE; i++) {
            prog[i] = opcodes::NOP;
        }

        unsigned int counter = 0;
        for (std::string line; getline(f, line);) {
            if (counter >= BE8bitCPU::RAM::MAX_SIZE) break;
            interpretLine(line, prog, counter);
        }

        f.close();
        return prog;
    }

    std::cout << "Unable to open file path.";
    exit(1);
}

void BE8bitCPU::Assembler::interpretLine(std::string line, uint8_t prog[], unsigned int& counter)
{
    if (line == std::string("")) return;

    std::vector<std::string> ins = split(split(line, ';')[0], ' ');
    if (ins.size() < 1) return;
    std::vector<std::string> vals = std::vector<std::string>(ins.begin() + 1, ins.end());

    if (std::isdigit(ins[0][0])) { // Write value to current address
        prog[counter] = stobyte(ins[0]);
        counter++;
    }
    else if (ins[0][0] == '@') { // Write values to specific address
        uint8_t address = stobyte(ins[0].substr(1));
        writeValues(address, vals, counter, prog);
    }
    else if (ins[0] == "NOP") writeInstruction(BE8bitCPU::opcodes::NOP, 0               , counter, prog);
    else if (ins[0] == "LDA") writeInstruction(BE8bitCPU::opcodes::LDA, stobyte(vals[0]), counter, prog);
    else if (ins[0] == "ADD") writeInstruction(BE8bitCPU::opcodes::ADD, stobyte(vals[0]), counter, prog);
    else if (ins[0] == "SUB") writeInstruction(BE8bitCPU::opcodes::SUB, stobyte(vals[0]), counter, prog);
    else if (ins[0] == "STA") writeInstruction(BE8bitCPU::opcodes::STA, stobyte(vals[0]), counter, prog);
    else if (ins[0] == "LDI") writeInstruction(BE8bitCPU::opcodes::LDI, stobyte(vals[0]), counter, prog);
    else if (ins[0] == "JMP") writeInstruction(BE8bitCPU::opcodes::JMP, stobyte(vals[0]), counter, prog);
    else if (ins[0] == "JC" ) writeInstruction(BE8bitCPU::opcodes::JC , stobyte(vals[0]), counter, prog);
    else if (ins[0] == "JZ" ) writeInstruction(BE8bitCPU::opcodes::JZ , stobyte(vals[0]), counter, prog);
    else if (ins[0] == "OUT") writeInstruction(BE8bitCPU::opcodes::OUT, 0               , counter, prog);
    else if (ins[0] == "HLT") writeInstruction(BE8bitCPU::opcodes::HLT, 0               , counter, prog);
}