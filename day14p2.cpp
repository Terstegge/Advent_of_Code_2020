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

    long	mask_x;
    long	mask_or;
    string	mask_raw;

    while (ifs.good()) {
        string left, right;
        ifs >> left;
        char c;
        ifs >> c;
        ifs >> right;

        /////////
        // MEM //
        /////////
        if (left.substr(0,3) == "mem") {
            size_t open  = left.find("[");
            size_t close = left.find("]");
            long addr = stoi( left.substr(open+1, close - open -1) );
            long data = stol( right );

            // Prepare addr
            addr &= ~mask_x;  // reset all x bits
            addr |=  mask_or; // set all 1 bits

            // Permute all X combinations
            int count = std::count_if( mask_raw.begin(), mask_raw.end(), [](char c) { return c=='X'; } );
//            cout << "Count: " << count << endl;

            for (long iter=0; iter < (1 << count); ++iter) {
                long val = 0;
                long mask_iter = 1;
                for (long bit=0; bit < mask_raw.size(); ++bit) {
                    if (mask_x & (1L<<bit)) {
                        if (iter & mask_iter) {
                            val |= (1L<<bit);
                        }
                        mask_iter <<= 1;
                    }
                }
//                cout << hex << iter << "Writing " << setw(9) << (addr | val) << endl;
                mem[addr | val] = data;
            }
        } else 

        //////////
        // MASK //
        //////////
        if (left.substr(0,4) == "mask") {
            if (right.size() != 36) {
                cout << "Wrong mask size: " << right << endl;
                break;
            }
            mask_x   = 0;
            mask_or  = 0;
            mask_raw = right;

            for (auto & c : right) {
                mask_x  <<= 1;
                mask_or <<= 1;
                switch(c) {
                    case '0': {
                        mask_or |= 0; // No set
                        break;
                    }
                    case '1':{
                        mask_or |= 1; // Set
                        break;
                    }
                    default: {
                        mask_x |= 1; // Store X
                        break;
                    }
                }  
            }
            cout << "** " << right << endl;
            cout << "Mask X : " << hex << mask_x  << endl;
            cout << "Mask OR: " << hex << mask_or << endl;
        } else {
            cout << "Unknown left side " << left << endl;
            break;
        }
    }
    
    // Sum of all values
    long res = 0;
    for (auto & e : mem) res += e.second;
    
    cout << dec << "\nSum: " << res << endl;  
    
}
