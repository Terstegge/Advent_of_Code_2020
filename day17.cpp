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
#include <sstream>
#include <array>

using namespace std;

typedef vector<bool>	ROW;
typedef vector<ROW>  	PLANE;
typedef vector<PLANE>	VOLUME;

int iterations = 6;
int width;

void empty_volume(VOLUME & v) {
    v.clear();
    for (int z=0; z < (iterations+1)*2+1; ++z) {
        PLANE p;
        for (int y=0; y < (iterations+1)*2+width; ++y) {
            ROW r;
            for (int x=0; x < (iterations+1)*2+width; ++x) {
                r.push_back(false);
            }
            p.push_back(r);
        }
        v.push_back(p);
    }
}

void show_volume(VOLUME & v) {
    for (int z=0; z < (iterations+1)*2+1; ++z) {
        for (int y=0; y < (iterations+1)*2+width; ++y) {
            for (int x=0; x < (iterations+1)*2+width; ++x) {
                cout << v[z][y][x] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

int count_nacharn(VOLUME & v, int z, int y, int x) {
    int res = 0;
    for (int dz=-1; dz <=1; dz++) {
        for (int dy=-1; dy <=1; dy++) {
            for (int dx=-1; dx <=1; dx++) {
                if (dz==0 && dy==0 && dx==0) continue;
                if (v[z+dz][y+dy][x+dx]) res++;
            }
        }
    }
    return res;
}


int main() {

    // Read in a plane
    //////////////////
    ifstream ifs;
    ifs.open("day17.dat");
    string s;
    getline(ifs, s);
    width = s.size();

    VOLUME v;
    empty_volume(v);

    // Read in data
    int y = iterations+1;
    while(s.size()) {
        for(int x=0; x < width; x++) {
            v[iterations+1][y][x+iterations+1] = (s[x]=='#');
        }
        y++;
        getline(ifs, s);
    }

    VOLUME tmp;
    for(int iter=0; iter < 6; iter++) {
        empty_volume(tmp);
        for(int z=1; z < (v.size()-1); z++) {
            for(int y=1; y < (v[0].size()-1); y++) {
                for(int x=1; x < (v[0][0].size()-1); x++) {
                    int cnt = count_nacharn(v, z, y, x);
                    if ( v[z][y][x] && (cnt==2 || cnt==3)) tmp[z][y][x] = true;                    
                    if (!v[z][y][x] && (cnt==3))           tmp[z][y][x] = true;                    
                }
            }
        }
        show_volume(tmp);
        v = tmp;
    }

    // Count
    ////////
    int count=0;
    for (int z=0; z < (iterations+1)*2+1; ++z) {
        for (int y=0; y < (iterations+1)*2+width; ++y) {
            for (int x=0; x < (iterations+1)*2+width; ++x) {
                if (v[z][y][x]) count++;
            }
        }
    }
    cout << "Count: " << count << endl;
}
