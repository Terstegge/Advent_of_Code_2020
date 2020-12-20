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
typedef vector<VOLUME>	HYPER;

int iterations = 6;
int width;

void empty_hyper(HYPER & h) {
    h.clear();
    for (int w=0; w < (iterations+1)*2+1; ++w) {
        VOLUME v;
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
        h.push_back(v);
    }
}

#if 0
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
#endif

int count_nacharn(HYPER & h, int w, int z, int y, int x) {
    int res = 0;
    for (int dw=-1; dw <=1; dw++) {
        for (int dz=-1; dz <=1; dz++) {
            for (int dy=-1; dy <=1; dy++) {
                for (int dx=-1; dx <=1; dx++) {
                    if (dw==0 && dz==0 && dy==0 && dx==0) continue;
                    if (h[w+dw][z+dz][y+dy][x+dx]) res++;
                }
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

    HYPER h;
    empty_hyper(h);

    // Read in data
    int w = iterations+1;
    int z = iterations+1;
    int y = iterations+1;
    while(s.size()) {
        for(int x=0; x < width; x++) {
            h[w][z][y][x+iterations+1] = (s[x]=='#');
        }
        y++;
        getline(ifs, s);
    }

    HYPER tmp;
    for(int iter=0; iter < 6; iter++) {
        empty_hyper(tmp);
        for(int w=1; w < (h.size()-1); w++) {
            for(int z=1; z < (h[0].size()-1); z++) {
                for(int y=1; y < (h[0][0].size()-1); y++) {
                    for(int x=1; x < (h[0][0][0].size()-1); x++) {
                        int cnt = count_nacharn(h, w, z, y, x);
                        if ( h[w][z][y][x] && (cnt==2 || cnt==3)) tmp[w][z][y][x] = true;                    
                        if (!h[w][z][y][x] && (cnt==3))           tmp[w][z][y][x] = true;                    
                    }
                }
            }
        }
//        show_volume(tmp);
        h = tmp;
    }

    // Count
    ////////
    int count=0;
    for (int w=0; w < (iterations+1)*2+1; ++w) {
        for (int z=0; z < (iterations+1)*2+1; ++z) {
            for (int y=0; y < (iterations+1)*2+width; ++y) {
                for (int x=0; x < (iterations+1)*2+width; ++x) {
                    if (h[w][z][y][x]) count++;
                }
            }
        }
    }
    cout << "Count: " << count << endl;
}
