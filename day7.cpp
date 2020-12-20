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

struct entry {
    int	count;
    string type;
};


int recurse(const string & type, int n, unordered_map<string, vector<entry>> & rules) {
    
    int res = n;
    if (rules.count(type)) {
        for (auto & e : rules[type]) {
            res += n * recurse(e.type, e.count, rules);
        }
    }
    return res;
} 



int main() {

    unordered_map<string, vector<entry>> rules;

    ifstream ifs;
    ifs.open("day7.dat");
    entry e;
    
    while (ifs.good()) {
        // Get the key
        string key, tmp;
        ifs >> key >> tmp;
        key += " " + tmp;
        // checks
        if (!tmp.size()) break;
        ifs >> tmp;
        assert( tmp == "bags");
        ifs >> tmp;
        assert( tmp == "contain");
        // Get entries
        do {
            string num;
            ifs >> num;
            if (num == "no") {
                ifs >> tmp; // other
                rules[key].begin(); // add empty entry
            } else {
                e.count = stoi(num);
                ifs >> e.type >> tmp;
                e.type += " " + tmp;
                rules[key].push_back(e);
            }
            string bags;
            ifs >> bags;
            if (bags == "bags." || bags == "bag.") break;            
        } while (true);
    }

    cout << "Data okay" << endl;
    cout << "Size: " << rules.size() << endl;

    map<string, int> colors;
    colors["shiny gold"]++;

    // Part 1
    int before, after;
    do {
        before = colors.size();
        for (auto & r : rules) {
            for (auto & e : r.second) {
                if (colors.count(e.type)) {
                    colors[r.first]++;
                }
            }
        }
        after = colors.size();
    }
    while(before != after);
    cout << "Colors Size: " << colors.size()-1 << endl;

    // Part 2
    cout << recurse("shiny gold", 1, rules)-1 << endl;    
}

