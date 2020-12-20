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

int main() {

    vector<long long> data;

    ifstream ifs;
    ifs.open("day9.dat");
    
    while (ifs.good()) {
        long long i;
        ifs >> i;
        if (ifs.good()) data.push_back(i);
    }

    cout << "Data okay" << endl;
    cout << "Size: " << data.size() << endl;

    int PREABEL_LEN = 25;
    int i, j, k;

    // Part 1
    // Loop over all numbers to check
    for (i = PREABEL_LEN; i < data.size(); ++i) {
        // Loop over all 25 numbers before
        bool found = false;
        for (j=i-PREABEL_LEN; j < i; j++) {
            for (k=i-PREABEL_LEN; k < i; k++) {
                if ( (data[i] == (data[j] + data[k])) &&
                     (data[j] != data[k]) ) {
                     found = true;
                     break;
                }
            }
            if (found) break;
        }
        if (!found) {
            cout << "Error at number " << data[i] << endl;
            break;
        }
    }

    // Part 2
    long long invalid = data[i];
    // i ist start of range
    for (i = 0; i < data.size(); ++i) {
        long long sum = 0;
        k = i;
        while (sum < invalid) sum += data[k++];
        if (sum == invalid) {
            cout << "Found range:" << i << " " << (k-1) << endl;
            break;
        }
    }
    std::sort(&data[i], &data[k]);
    cout << "Min+Max = " << data[i] + data[k-1] << endl;
}

