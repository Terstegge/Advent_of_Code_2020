#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <cctype>

using namespace std;

int main() {

    vector< unordered_map<char, int> > data;
    
    ifstream ifs;
    ifs.open("day6.dat");
    unordered_map<char, int> entry;
    
    while (ifs.good()) {
        string s;
        ifs >> s;
        for (char c : s) entry[c]++;
        entry['#']++;
        char c1 = ifs.get();
        char c2 = ifs.get();
        if ((c1 == '\n') && (c2 == '\n')) {
            // Store entry
            data.push_back( entry );
            entry.clear();
        } else {
            ifs.putback(c2);
            ifs.putback(c1);
        }
    }
    if (entry.size()) {
        data.push_back( entry );
        entry.clear();
    }

    cout << "Data okay" << endl;
    cout << "Size: " << data.size() << endl;

    int sum = 0;
    for (auto e : data) {
        for (auto c : e) {
        
            if (c.second == e['#'] && (c.first != '#')) {
                cout << "All voted " << c.first << endl;
                sum++;
            }
        }
        cout << "Current: " << sum << endl;
    }
    cout << "Sum: " << sum << endl;
}
