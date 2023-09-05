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

void WriteVariables(Byte start_adr, vector<string> values, Byte& counter, Byte prog[]) {
    for (int i = 0; i < values.size(); i++) {
        if (start_adr + i >= RAM::MAX_SIZE) break;
        Byte value = stoi(values[i], NULL, 0);
        prog[start_adr + i] = value;
        counter += (start_adr + i == counter);
    }
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
            WriteVariables(address, vals, counter, prog);
        }
        else if (ins == "NOP") {
            prog[counter] = opcodes::NOP;
            counter++;
        }
        else if (ins == "LDA") {
            prog[counter] = opcodes::LDA + stoi(vals[0], NULL, 0);
            counter++;
        }
        else if (ins == "ADD") {
            prog[counter] = opcodes::ADD + stoi(vals[0], NULL, 0);
            counter++;
        }
        else if (ins == "SUB") {
            prog[counter] = opcodes::SUB + stoi(vals[0], NULL, 0);
            counter++;
        }
        else if (ins == "OUT") {
            prog[counter] = opcodes::OUT;
            counter++;
        }
        else if (ins == "HLT") {
            prog[counter] = opcodes::HLT;
            counter++;
        }

        if (counter >= RAM::MAX_SIZE) {
            cout << "\\ Reached end of file. \n";
            break;
        }
    }

    cout << '{';
    printf("0x%02x", prog[0]);
    for (int i = 1; i < RAM::MAX_SIZE; i++) {
        printf(", 0x%02x", prog[i]);
    }
    cout << '}';

    return 0;
}