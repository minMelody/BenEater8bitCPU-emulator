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
        if (subst.length() > 1) vec.push_back(subst);
        str.erase(0, pos + 1);
    }
    vec.push_back(str);
    return vec;
}

int main()
{
    cout << '\\' << '\n';
    Byte prog[RAM::MAX_SIZE]{ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
    Byte counter = 0;

    string input;
    while (getline(cin, input)) {
        if (input == string("\\")) break;

        vector<string> line = split(input, ' ');
        
        if (line[0][0] == '@') {
            Byte address = stoi(line[0].substr(1));
            prog[address] = stoi(line[1]);
            counter += (address == counter);
        }
        else if (string(line[0]) == "LDA") {
            prog[counter] = opcodes::LDA + stoi(line[1]);
            counter++;
        }
        else if (string(line[0]) == "ADD") {
            prog[counter] = opcodes::ADD + stoi(line[1]);
            counter++;
        }
        else if (string(line[0]) == "OUT") {
            prog[counter] = opcodes::OUT;
            counter++;
        }

        if (counter >= RAM::MAX_SIZE - 1) {
            cout << '\\' << '\n';
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