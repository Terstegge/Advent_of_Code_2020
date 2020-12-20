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

int main() {

    // Number and vector of indizes
    map<int, vector<int>> data;

    int idx = 0;
        
    data[20].push_back(idx++);
    data[ 9].push_back(idx++);
    data[11].push_back(idx++);
    data[ 0].push_back(idx++);
    data[ 1].push_back(idx++);
    data[ 2].push_back(idx++);

    int last = 2;

    while (idx < 30000000) {
        if (data[last].size() == 1) {
            last = 0;
            data[last].push_back(idx++);
        } else {
//            cout << idx << " " << data[last].size() << endl;
            last = data[last][ data[last].size() -1 ] -
                   data[last][ data[last].size() -2 ];
            data[last].push_back(idx++);
        }
//        cout << idx << "\r"; // << endl;
    }
        cout << endl << endl << last << endl;
}

