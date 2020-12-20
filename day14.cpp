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
#include <iomanip>

using namespace std;

map<long, long> mem;

int main() {

    ifstream ifs;
    ifs.open("day14.dat");

    while (ifs.good()) {
        string left, right;
        ifs >> left;
        char c;
        ifs >> c;
        ifs >> right;

        long mask_and;
        long mask_or;

        if (left.substr(0,3) == "mem") {
            size_t open  = left.find("[");
            size_t close = left.find("]");
            long addr = stoi( left.substr(open+1, close - open -1) );
            long data = stol( right );
            cout << setw(9) << hex << data << " (Data: "  << dec << data << " at " << addr << ")" << endl;
            cout << setw(9) << hex << mask_and << " (AND)" << endl;
            cout << setw(9) << hex << mask_or  << " (OR)"  << endl;
            data &= mask_and;
            data |= mask_or;
            mem[addr] = data;
            cout << setw(9) << hex << data << " (RESULT)" << endl; 
        } else 
        if (left.substr(0,4) == "mask") {
            if (right.size() != 36) {
                cout << "Wrong mask size: " << right << endl;
                break;
            }
            mask_and = 0;
            mask_or  = 0;
            for (auto & c : right) {
                mask_and <<= 1;
                mask_or  <<= 1;
                switch(c) {
                    case '0': {
                        mask_and |= 0; // Reset
                        mask_or  |= 0; // No set
                        break;
                    }
                    case '1':{
                        mask_and |= 1; // No Reset
                        mask_or  |= 1; // Set
                        break;
                    }
                    default: {
                        mask_or  |= 0; // No Set
                        mask_and |= 1; // No Reset
                        break;
                    }
                }  
            }
            cout << "** " << right << endl;
            cout << "Mask AND: " << hex << mask_and << endl;
            cout << "Mask OR : " << hex << mask_or  << endl;
        } else {
            cout << "Unknown left side " << left << endl;
            break;
        }
    }
    
    // Part 1: Sum of all values
    long res = 0;
    for (auto & e : mem) res += e.second;
    
    cout << dec << "\nSum: " << res << endl;  
    
}

