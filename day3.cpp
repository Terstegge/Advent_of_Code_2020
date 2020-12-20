#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

int calc(vector<string> & data, int dx, int dy) {
    int x = dx;
    int y = dy;
    int trees = 0;
    
    do {
      if ( data[y][x] == '#' ) trees++;
      x += dx;
      x %= data[y-dy].size();
      y += dy;
    } while (y < data.size());
    return trees;
}


int main() {

    vector<string> data;
    
    ifstream ifs;
    ifs.open("day3.dat");
    
    while (ifs.good()) {
        string s;
        getline(ifs, s);
        data.push_back(s);
    }

    cout << "Data okay" << endl;
    cout << "Size: " << data.size() << endl;

    cout << calc(data, 1, 1) << endl;
    cout << calc(data, 3, 1) << endl;
    cout << calc(data, 5, 1) << endl;
    cout << calc(data, 7, 1) << endl;
    cout << calc(data, 1, 2) << endl;
}
