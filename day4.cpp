#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <cctype>

using namespace std;

bool check_byr(unordered_map<string, string> & e) {
    if (e["byr"].size() != 4) return false;
    istringstream iss(e["byr"]);
    int year;
    iss >> year;
    if (year >= 1920 && year <= 2002) return true;
    return false;
}

bool check_iyr(unordered_map<string, string> & e) {
    if (e["iyr"].size() != 4) return false;
    istringstream iss(e["iyr"]);
    int year;
    iss >> year;
    if (year >= 2010 && year <= 2020) return true;
    return false;
}

bool check_eyr(unordered_map<string, string> & e) {
    if (e["eyr"].size() != 4) return false;
    istringstream iss(e["eyr"]);
    int year;
    iss >> year;
    if (year >= 2020 && year <= 2030) return true;
    return false;
}

bool check_hgt(unordered_map<string, string> & e) {
    istringstream iss(e["hgt"]);
    int h;
    string u;
    iss >> h >> u;
    if (u == "cm") return (h >=150) && (h <= 193);
    if (u == "in") return (h >= 59) && (h <=  76);
    return false;
}

bool check_hcl(unordered_map<string, string> & e) {
    istringstream iss(e["hcl"]);
    char hash;
    string v;
    iss >> hash >> v;
    if (hash != '#')   return false;
    if (v.size() != 6) return false;
    for (char c : v) {
        if (!(isdigit(c) || (c >= '0' && c <= 'f')) ) {
            return false;
        }        
    }
    return true;
}

bool check_ecl(unordered_map<string, string> & e) {
    string col = e["ecl"];
    if (col == "amb") return true;
    if (col == "blu") return true;
    if (col == "brn") return true;
    if (col == "gry") return true;
    if (col == "grn") return true;
    if (col == "hzl") return true;
    if (col == "oth") return true;
    return false;
}

bool check_pid(unordered_map<string, string> & e) {
    string pid = e["pid"];
    if (pid.size() != 9) return false;
    for (char c : pid) {
        if (!isdigit(c)) {
            return false;
        }        
    }
    return true;
}


int main() {

    vector< unordered_map<string, string> > data;
    
    ifstream ifs;
    ifs.open("day4.dat");
    unordered_map<string, string> entry;
    
    while (ifs.good()) {
        string s;
        ifs >> s;
        int colon = s.find(':');
        string name  = s.substr(0, colon);
        string value = s.substr(colon+1); 
        entry[name] = value;
        char c1 = ifs.get();
        char c2 = ifs.get();
        if ((c1 == '\n') && (c2 == '\n')) {
            // Store entry
            data.push_back( entry );
            entry.clear();
        } else {
            ifs.putback(c2);
            ifs.putback(c1);
        }
    }
    if (entry.size()) {
        data.push_back( entry );
        entry.clear();
    }

    cout << "Data okay" << endl;
    cout << "Size: " << data.size() << endl;

    int valid = 0;
    for (auto & e : data) {
        if (check_byr(e) &&
            check_iyr(e) &&
            check_eyr(e) &&
            check_hgt(e) &&
            check_hcl(e) &&
            check_ecl(e) &&
            check_pid(e)) valid++;
    }
    cout << "Valid: " << valid << endl;
}
