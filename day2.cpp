#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

struct entry {
    int min;
    int max;
    char c;
    string pwd;
};

int main() {

    vector<entry> data;
    
    ifstream ifs;
    ifs.open("day2.dat");
    
    while (ifs.good()) {
        entry e;
        ifs >> e.min;
        ifs >> e.max;
        e.max *= -1;
        ifs >> e.c;
        char dummy;
        ifs >> dummy;
        ifs >> e.pwd;

        cout << e.min << " ";
        cout << e.max << " ";
        cout << e.c << " ";
        cout << e.pwd << endl;

        data.push_back(e);
    }

    int valid = 0;
    for (int i=0; i < data.size(); ++i) {
    
      int min = data[i].min -1;
      int max = data[i].max -1;
      
      if ( (data[i].pwd[min] == data[i].c) ^ 
           (data[i].pwd[max] == data[i].c) ) {
           valid++;
      }
//        int count = count_if(data[i].pwd.begin(), data[i].pwd.end(),
//                             [&](char & c) { return c == data[i].c; } );
//        if ((count >= data[i].min) && (count <= data[i].max)) {
//          valid++;
//        }
    }

    cout << valid << endl;

}