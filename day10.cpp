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

using namespace std;

// Calculate all combinations between
// indices min and max (inclusive)
/////////////////////////////////////
int recurse(int min, int max, vector<int> & data) {
    // Abbruch
    if (min == max) return 1;
    int val = data[min];
    int res = 0;
    min++;
    // Find all next possible adapters
    while ( (min <= max) && ((data[min]-val) <= 3) ) {
        res += recurse(min++, max, data);
    }
    return res;
}

int main() {

    vector<int> data;

    data.push_back(0); // The 0 joltage outlet

    ifstream ifs;
    ifs.open("day10.dat");
    
    while (ifs.good()) {
        int i;
        ifs >> i;
        if (ifs.good()) data.push_back(i);
    }

    cout << "Data okay" << endl;
    cout << "Size: " << data.size() << endl;

    std::sort(data.begin(), data.end());
    
    data.push_back( data[data.size()-1] + 3 ); // Device input

    // Part 1
    int count1 = 0;
    int count3 = 0;
    for (int i=0; i < (data.size() -1); ++i) {
        if ((data[i+1] - data[i]) > 3) {
            cout << "Error in data at index " << i << endl;
            break;
        }
        if ((data[i+1] - data[i]) == 1) count1++;
        if ((data[i+1] - data[i]) == 3) count3++;
    }
    cout << count1 << " " << count3 << " " << count1 * count3 << endl;

    // Part 2
    long long combis = 1;
    int min = 0, max = 1;
    do {
        // Find a delta of 3 and ...
        while((max < data.size()) && (data[max]-data[max-1]) < 3) max++; 
        // ...calculate all combinations up to this index
        combis *= recurse(min, max, data);
        // Continue with next section
        min = max;
        max++;
    } while(max < data.size());
    cout << combis << endl;
}

