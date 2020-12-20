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


// Part 1 algorithm
///////////////////
int count_occupied(int y, int x, const vector<string> & area) {
    int res = 0;
    if (area[y-1][x-1] == '#') res++;
    if (area[y-1][x  ] == '#') res++;
    if (area[y-1][x+1] == '#') res++;
    if (area[y+1][x-1] == '#') res++;
    if (area[y+1][x  ] == '#') res++;
    if (area[y+1][x+1] == '#') res++;
    if (area[y  ][x-1] == '#') res++;
    if (area[y  ][x+1] == '#') res++;
    return res;
}

// Part 2 algorithm
///////////////////
char ray(int y, int x, int dy, int dx, const vector<string> & area) {
    do {
        x += dx;
        y += dy;
    }
    while ( (x >= 1) && (y >= 1 ) &&
            (x <= (area[0].size()-2)) &&
            (y <=  area.size()-2) &&
            (area[y][x] == '.') );

    return area[y][x];
}

int count_occupied2(int y, int x, const vector<string> & area) {
    int res = 0;
    if (ray(y, x,  0,  1, area) == '#') res++;
    if (ray(y, x,  1,  1, area) == '#') res++;
    if (ray(y, x,  1,  0, area) == '#') res++;
    if (ray(y, x,  1, -1, area) == '#') res++;
    if (ray(y, x,  0, -1, area) == '#') res++;
    if (ray(y, x, -1, -1, area) == '#') res++;
    if (ray(y, x, -1,  0, area) == '#') res++;
    if (ray(y, x, -1,  1, area) == '#') res++;
    return res;
}

int main() {

    vector<string> data;

    ifstream ifs;
    ifs.open("day11.dat");
    
    while (ifs.good()) {
        string s;
        ifs >> s;
        if (ifs.good()) data.push_back(s);
    }

    cout << "Data okay" << endl;
    cout << "Size: " << data.size() << endl;

    int width = data[0].size();
    cout << "Width: " << width << endl;

    vector<string> area;
    area.push_back(string(width+2, '.'));    
    for (auto & e : data) {
        string s = "." + e + ".";
        area.push_back(s);
    }
    area.push_back(string(width+2, '.'));    

    bool changed;
    do {
        changed = false;
        auto copy = area;
        for (int x=1; x <= width; ++x) {
            for(int y=1; y <= data.size(); ++y) {
                switch(area[y][x]) {
                    case 'L': {
                        if (count_occupied2(y,x,area) == 0) {
                            copy[y][x] = '#';
                            changed = true;
                        }
                        break;
                    }
                    case '#': {
                        if (count_occupied2(y,x,area) >= 5) {
                            copy[y][x] = 'L';
                            changed = true;
                        }
                        break;
                    }
                }
            }
        }
        
        if (changed) area = copy;
        // Print new state
        for (auto & e : area) cout << e << endl;
        cout << endl;

    } while (changed);

    // Count occupied
    int oc = 0;
    for (int x=1; x <= width; ++x) {
        for(int y=1; y <= data.size(); ++y) {
            if (area[y][x] == '#') oc++;
        }
    }
    cout << oc << endl;
}

