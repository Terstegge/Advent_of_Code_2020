#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

int main() {

    vector<int> data;
    int d;
    
    ifstream ifs;
    ifs.open("day1.dat");
    
    while (ifs.good()) {
        ifs >> d;
        data.push_back(d);
    }

    for (int i=0; i < data.size(); ++i) {
        for (int j=i+1; j < data.size(); ++j) {
            for (int k=j+1; k < data.size(); ++k) {

                if (data[i] + data[j] + data[k] == 2020) {
                    cout << data[i] << " " << data[j] << " " << data[k] << endl;
                }
            }
        }
    }

    cout << data.size() << endl;

}