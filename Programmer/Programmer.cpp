#include <iostream>
#include <string>
#include <vector>
#include "../BE8bitCPU.h"

using namespace std;
using namespace BE8bitCPU;

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

void writeValues(Byte start_adr, vector<string> values, Byte& counter, Byte prog[]) {
    for (int i = 0; i < values.size(); i++) {
        if (start_adr + i >= RAM::MAX_SIZE) break;
        Byte value = stoi(values[i], NULL, 0);
        prog[start_adr + i] = value;
        counter += (start_adr + i == counter);
    }
}

void writeInstruction(Byte opcode, Byte data, Byte& counter, Byte prog[]) {
    prog[counter] = opcode + (data & 0x0f);
    counter++;
}

int main()
{
    cout << '>' << '\n';
    Byte prog[RAM::MAX_SIZE]{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
    Byte counter = 0;

    string input;
    while (getline(cin, input)) {
        if (input == string("")) continue;
        vector<string> line = split(split(input, ';')[0], ' ');

        if (line[0] == string("\\")) break;

        string ins = line[0];
        vector<string> vals = vector<string>(line.begin() + 1, line.end());

        if (ins[0] == '@') {
            Byte address = stoi(ins.substr(1), NULL, 0);
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

    // print out compiled program
    cout << '{';
    printf("0x%02x", prog[0]);
    for (int i = 1; i < RAM::MAX_SIZE; i++) {
        printf(", 0x%02x", prog[i]);
    }
    cout << '}';

    return 0;
}