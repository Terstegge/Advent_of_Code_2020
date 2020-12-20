#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

int main() {

    vector<string> data;
    vector<int> ids;
    
    ifstream ifs;
    ifs.open("day5.dat");

    int maxid = 0;
        
    while (ifs.good()) {
        string s;
        getline(ifs, s);
        if (s.size()) {
            int mask = 64;
            int row  = 0;
            for (int i=0; i < 7; ++i) {
                if (s[i] == 'B') row += mask;
                mask >>= 1;
            }

            mask = 4;
            int col  = 0;
            for (int i=7; i < 10; ++i) {
                if (s[i] == 'R') col += mask;
                mask >>= 1;
            }

            int id = row * 8 + col;
            ids.push_back(id);
            
            cout << s << " --> " << "Row: " << row << " Col: " << col << " ID: " << id << endl;

            if (id > maxid) maxid = id;
            data.push_back(s);
        }
    }

    std::sort(ids.begin(), ids.end());
    
    for (int i=0; i < (ids.size()-1); ++i) {
        if ((ids[i]+1) != ids[i+1]) {
            cout << "Gap detected: " << ids[i] << " " << ids[i+1] << endl;
        }
    }
    
    cout << "Max: " << maxid << endl;
    cout << "Data okay" << endl;
    cout << "Size: " << data.size() << endl;

    

}
