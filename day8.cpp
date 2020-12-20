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

enum inst_code { ACC, JMP, NOP };

struct ENTRY {
    bool 	exec;
    inst_code	inst;
    int		param;
};

typedef vector<ENTRY> PRGM;

bool execute(PRGM & prgm) {
    int PC = 0;
    int A  = 0;
    // Reset exec flags
    for (auto & i : prgm) i.exec = false;
    while (!prgm[ PC ].exec && (PC < prgm.size()) ) {
        prgm[PC].exec = true; // Mark as executed
        switch(prgm[PC].inst) {
            case ACC: { A  += prgm[PC].param; PC++; break;}
            case JMP: { PC += prgm[PC].param; break; }
            case NOP: { PC ++; break; }
        }
    }
    cout << "Akku: " << A << endl;
    // Check if we ended immediately after the last instruction
    return PC == prgm.size();
}


int main() {

    PRGM prgm;

    ifstream ifs;
    ifs.open("day8.dat");
    ENTRY e;
    
    while (ifs.good()) {
        // Get the key
        string inst;
        int param;
        ifs >> inst >> param;
        e.exec  = false;
        e.param = param;
        if (inst == "acc") {
            e.inst  = ACC;
            prgm.push_back(e);
        }
        if (inst == "jmp") {
            e.inst  = JMP;
            prgm.push_back(e);
        }
        if (inst == "nop") {
            e.inst  = NOP;
            prgm.push_back(e);
        }
    }

    cout << "Data okay" << endl;
    cout << "Size: " << prgm.size() << endl;

    // Part 1
    execute( prgm );

    // Part 2
    vector<PRGM> prgms;
    for (int i=0; i < prgm.size(); ++i) {
        if (prgm[i].inst == JMP) {
            PRGM p = prgm;
            p[i].inst = NOP;
            prgms.push_back(p);
        } else if (prgm[i].inst == NOP) {
            PRGM p = prgm;
            p[i].inst = JMP;
            prgms.push_back(p);
        }
    }
    cout << "Generated " << prgms.size() << " Programs" << endl;

    for (auto & p : prgms) {
        if (execute(p)) {
            cout << "Last programm terminated correctly" << endl;
        }
    }
}

