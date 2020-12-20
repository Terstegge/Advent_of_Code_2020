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

struct ENTRY {
    int id;
    int idx;
};

vector<ENTRY> buses;

int main() {

    ifstream ifs;
    ifs.open("foo");

    int  ts;
    ifs >> ts;

    
    int i    = 0;
    while (ifs.good()) {
        int val;
        ifs >> val;
        if (ifs.good()) {
            if (!val) {
                i++;
                continue;
            } 
            ENTRY e;
            e.id  = val;
            e.idx = i++;
            buses.push_back(e);
        }
    }
    cout << buses.size() << endl;
    cout << "First: " << buses[0].id << " Last: " << buses[buses.size()-1].id << endl;

    long long dep = 0;
    long long inc = 1;
    for (auto & e : buses) {
        // Find next match
        while ((dep + e.idx) % e.id) dep += inc;
        cout << "Found: " << dep << endl;
        inc *= e.id;
    }
    cout << "\n\nDeparture: " << dep << endl;

#if 0
    int minttw = 9999999;
    int minid  = 0;
    
    for (int i=0; i < buses.size(); ++i) {
        int z = ts % buses[i];
        if (z==0) {
            minttw = 0;
            minid  = i;
        } else {
            int ttw = buses[i] - z;
            if (ttw < minttw) {
                minttw = ttw;
                minid  = i;
            }
        }
           
    }
    cout << "ID: " << buses[minid] << " TTW: " << minttw << endl;
#endif

}

