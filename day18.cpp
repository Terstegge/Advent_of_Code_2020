#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <sstream>
#include <cctype>
#include <cassert>
#include <sstream>
#include <array>

using namespace std;

enum OP { NOP, ADD, MUL };

long evaluate(istream & is) {
    long res = 0;
    OP op = NOP;

    while (is.good()) {
        char c;
        if (!(is >> c)) return res; 
        
        switch(c) {
            case '0':  case '1':  case '2':  case '3':  case '4':
            case '5':  case '6':  case '7':  case '8':  case '9': {
                long num = c - '0';
                switch(op) {
                    case NOP: { res  = num; break; }
                    case ADD: { res += num; op = NOP; break; }
                    case MUL: { res *= num; op = NOP; break; }
                }
                break;
            }
            case '+': { op = ADD; break; }
            case '*': { op = MUL; break; } 
            case '(': {
                switch(op) {
                    case NOP: { res  = evaluate(is); break; }
                    case ADD: { res += evaluate(is); op = NOP; break; }
                    case MUL: { res *= evaluate(is); op = NOP; break; }
                }
                break;
            }
            case ')': { return res; }
            default: {
                cout << "Strange char in expression: " << c << endl;
            }
        }
    }
    return res;
}


int main() {

    // Read in a plane
    //////////////////
    ifstream ifs;
    ifs.open("day18.dat");

    string s;
    getline(ifs, s);
    
    long long sum = 0;
    while(s.size()) {
        cout << s << endl;
        istringstream iss(s);
        sum += evaluate(iss);
        getline(ifs, s);
    }

    cout << "Result: " << sum << endl;
}
