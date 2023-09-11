#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../BE8bitCPU.h"

using namespace std;
using namespace BE8bitCPU;

#if defined _DEBUG
#define OUT_FILE "../debug.bin"
#else
#define OUT_FILE argv[1]
#endif

vector<string> split(string str, char delimiter) {
    vector<string> vec;
    size_t pos = 0;
    while ((pos = str.find(delimiter)) != string::npos) {
        string subst = str.substr(0, pos);
        if (subst.length() > 0) vec.push_back(subst);
        str.erase(0, pos + 1);
    }
    if (str.length() > 0) vec.push_back(str);
    return vec;
}

void writeValues(uint8_t start_adr, vector<string> values, uint8_t& counter, uint8_t prog[]) {
    for (int i = 0; i < values.size(); i++) {
        if (start_adr + i >= RAM::MAX_SIZE) break;
        uint8_t value = stoi(values[i], NULL, 0);
        prog[start_adr + i] = value;
        counter += (start_adr + i == counter);
    }
}

void writeInstruction(uint8_t opcode, uint8_t data, uint8_t& counter, uint8_t prog[]) {
    prog[counter] = opcode + (data & 0x0f);
    counter++;
}

int main(int argc, char* argv[])
{
    cout << '>' << '\n';
    uint8_t prog[RAM::MAX_SIZE]{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
    uint8_t counter = 0;

    string input;
    while (getline(cin, input)) {
        if (input == string("")) continue;
        vector<string> line = split(split(input, ';')[0], ' ');

        if (line[0] == string("\\")) break;

        string ins = line[0];
        vector<string> vals = vector<string>(line.begin() + 1, line.end());

        if (ins[0] == '@') {
            uint8_t address = stoi(ins.substr(1), NULL, 0);
            writeValues(address, vals, counter, prog);
        }
        else if (ins == "NOP") writeInstruction(opcodes::NOP, 0                     , counter, prog);
        else if (ins == "LDA") writeInstruction(opcodes::LDA, stoi(vals[0], NULL, 0), counter, prog);
        else if (ins == "ADD") writeInstruction(opcodes::ADD, stoi(vals[0], NULL, 0), counter, prog);
        else if (ins == "SUB") writeInstruction(opcodes::SUB, stoi(vals[0], NULL, 0), counter, prog);
        else if (ins == "STA") writeInstruction(opcodes::STA, stoi(vals[0], NULL, 0), counter, prog);
        else if (ins == "LDI") writeInstruction(opcodes::LDI, stoi(vals[0], NULL, 0), counter, prog);
        else if (ins == "JMP") writeInstruction(opcodes::JMP, stoi(vals[0], NULL, 0), counter, prog);
        else if (ins == "JC" ) writeInstruction(opcodes::JC , stoi(vals[0], NULL, 0), counter, prog);
        else if (ins == "JZ" ) writeInstruction(opcodes::JZ , stoi(vals[0], NULL, 0), counter, prog);
        else if (ins == "OUT") writeInstruction(opcodes::OUT, 0                     , counter, prog);
        else if (ins == "HLT") writeInstruction(opcodes::HLT, 0                     , counter, prog);

        if (counter >= RAM::MAX_SIZE) {
            cout << "\\ Reached end of file. \n";
            break;
        }
    }

    // print out compiled program and write file
    ofstream outfile(OUT_FILE);
    cout << '{';
    printf("0x%02x", prog[0]);
    outfile << prog[0];
    for (int i = 1; i < RAM::MAX_SIZE; i++) {
        printf(", 0x%02x", prog[i]);
        outfile << prog[i];
    }
    cout << '}';
    outfile.close();

    return 0;
}