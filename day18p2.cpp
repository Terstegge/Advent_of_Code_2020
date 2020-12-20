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

#include "Taschenrechner.h"

int main() {

    // Read in a plane
    //////////////////
    ifstream ifs;
    ifs.open("day18.dat");

    string s;
    getline(ifs, s);
    
    long long sum = 0;
    while(s.size()) {
        cout << s << endl;
        Taschenrechner tr(s);
        sum += tr.getErgebnis();
        getline(ifs, s);
    }

    cout << "Result: " << sum << endl;
}
