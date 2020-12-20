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

//const int NORTH=0;
//const int EAST=1;
//const int SOUTH=2;
//const int WEST=3;

int main() {

//    int dir = EAST;
    int x = 0;
    int y = 0;
    
    int wpx = 10;
    int wpy = 1;
    
    ifstream ifs;
    ifs.open("day12.dat");

    
    while (ifs.good()) {
        char c;
        int val;
        ifs >> c >> val;

        if (!ifs.good()) break;

        cout << "Cmd: " << c << val << " ";
        
        switch(c) {
            case 'N': {
//                cout << "Go NORTH " << val << endl;
                wpy += val;
                cout << "wps: " << wpx << " " << wpy << endl;
                break;
            }
            case 'S': {
//                cout << "Go SOUTH " << val << endl;
                wpy -= val;
                cout << "wps: " << wpx << " " << wpy << endl;
                break;
            }
            case 'E': {
//                cout << "Go EAST " << val << endl;
                wpx += val;
                cout << "wps: " << wpx << " " << wpy << endl;
                break;
            }
            case 'W': {
//                cout << "Go WEST " << val << endl;
                wpx -= val;
                cout << "wps: " << wpx << " " << wpy << endl;
                break;
            }
            case 'L': {
                int j = val/90;
                if (val%90 != 0) {
                    cout << "Fehler bei L" << endl;
                }
                while (j) {
                    int tmp = wpx;
                    wpx = -wpy;
                    wpy = tmp;
                    j--;
                }
//                dir -= j;
//                while(dir < 0) dir += 4;
                cout << "wps: " << wpx << " " << wpy << endl;
                break;
            }
            case 'R': {
                int j = val/90;
                if (val%90 != 0) {
                    cout << "Fehler bei R" << endl;
                }
                while (j) {
                    int tmp = wpx;
                    wpx = wpy;
                    wpy = -tmp;
                    j--;
                }
//                dir += j;
//                dir %= 4;
                cout << "wps: " << wpx << " " << wpy << endl;
//                cout << "New dir: " << dir << endl;
                break;
            }
            case 'F': {
                x += wpx * val;
                y += wpy * val;
                cout << "new pos: " << x << " " << y << endl;
/*                switch(dir) {
                    case NORTH: y += val; cout << "Go NORTH " << val << endl; break;
                    case EAST:  x += val; cout << "Go EAST " << val << endl;break;
                    case SOUTH: y -= val; cout << "Go SOUTH " << val << endl;break;
                    case WEST:  x -= val; cout << "Go WEST " << val << endl;break;
                    default: cout << "Fehler dir" << endl;
                }
*/
                break;
            }
            default: {
                cout << "Fehler unknown" << endl;
                break;
            }
        }
    }

    cout << "X: " << x << " Y: " << y << endl;
}

