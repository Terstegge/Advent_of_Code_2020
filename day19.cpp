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

struct ENTRY {
    char 		c;
    vector<vector<int>>	refs;
};

map<int, ENTRY> rules;

// Check a message
//////////////////
bool check(int rulenum, string & msg, int & idx) {
    if (idx >= msg.size()) return false;

    ENTRY & rule = rules[rulenum];
    if (rule.refs.size()) {
        // Middle node
        //////////////
        for (auto ref : rule.refs) {
            // Check a single entry
            bool b = true;
            int tmp = idx;
            for (int i : ref) {
//                cout << "Check Rule " << i << " Idx: " << idx << endl;
                b &= check(i, msg, tmp);
                if (!b) break;    
            }

            if ((rulenum == 8) && b) {
//                while (check(42, msg, tmp)) cout << " " << tmp << " ";
            }
            
            if (b) {
                idx = tmp;
                return true;
            }
        }
        return false;
    } else {
        // Leaf node
        ////////////        
//        cout << "Check " << msg[idx] << idx << " = " << rule.c << endl;
        return(msg[idx++] == rule.c);
    }
}

int main() {
    ifstream ifs;
    ifs.open("day19.dat");
//    ifs.open("foo");

    // Read in Rules
    ////////////////
    int  i, num;
    char c;
    string s;
    getline(ifs, s);
    while(s.size()) {
        istringstream iss(s);
        ENTRY e;
        iss >> num >> c;
        if (c != ':') cout << "Colon format error!" << endl;
//        cout << "Rule No: " << num << endl;
        vector<int> ref;
        while(iss.good()) {
            iss >> ws;
            if (!iss.good()) break;
            c = iss.peek();
            if (c == '|') {
                iss >> c;
                e.refs.push_back(ref);
                ref.clear();
            } else
            if (isdigit(c)) {
                iss >> i;
                ref.push_back(i);
            } else
            if (c == '"') {
                iss >> c;
                iss >> e.c;
                iss >> c;
            } else {
                cout << "Unknown char: '" << c << "'" << endl;
            }
        }
        if (ref.size()) e.refs.push_back(ref);
        // Store rule
        rules[num] = e;
        // Read in next line
        getline(ifs, s);
    }
    cout << "Rules Size: " << rules.size() << endl;

#if 0
    // Print Rules
    //////////////
    for (auto & e : rules) {
        cout << e.first << ": ";
        if (e.second.refs.size()) {
            for (auto & u : e.second.refs) {
                for (int i : u) cout << i << " ";
                cout << ", ";
            }
        } else {
            cout << "\"" << e.second.c << "\"";
        }
        cout << endl;
    }
#endif
#if 0
    // Read in messages
    ///////////////////
    int count = 0;
    while(!s.size()) getline(ifs, s);
    do {
        cout << "Check message: " << s << " -> ";
        int idx=0;
        bool res = check(0, s, idx);
        cout << res << " " << idx << " -> " << (res && (idx == s.size())) << endl;
        if (res && (idx == s.size())) count++;
        getline(ifs, s);
    } while(s.size());
    cout << "Valid Messages: " << count << endl;
#endif

    // Read in messages
    vector<string> messages;
    while(!s.size()) getline(ifs, s);
    do {
        messages.push_back(s);
        getline(ifs, s);
    } while(s.size());
    cout << "Message Size: " << messages.size() << endl;

    // This is a hack: Substitute rule 8 with
    // 42, 42 42, 42 42 42 and so forth up to 20 times 42.
    // A better solution would be much more generic...
    int count = 0;
    rules[8].refs[0].clear();
    for (int i=0; i < 20; ++i) {
        rules[8].refs[0].push_back(42);
        for (auto & msg : messages) {
            int idx=0;
            bool res = check(0, msg, idx);
            if (res && (idx == msg.size())) count++;
        }
    }
    cout << "Valid Messages: " << count << endl;
}

