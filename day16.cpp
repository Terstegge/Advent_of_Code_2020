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

using namespace std;

struct RULE {
    string	name;
    int		min1;
    int		max1;
    int		min2;
    int		max2;

    vector<int> fits; // Columns which fit for this rule
};

typedef vector<int> TICKET;

vector<int> error_tickets;

int main() {

    vector<RULE>   rules;
    TICKET         your_ticket;
    vector<TICKET> nearby_tickets;

    ifstream ifs;
    ifs.open("day16.dat");
    
    // Read RULES
    /////////////
    string s;
    getline(ifs, s);
    while (s.size()) {
        RULE e;
        size_t colon = s.find(":");
        e.name = s.substr(0, colon);
        istringstream iss(s.substr(colon+1));
        string o;
        iss >> e.min1 >> e.max1 >> o >> e.min2 >> e.max2;
        e.max1 *= -1;
        e.max2 *= -1;
        if (o != "or") cout << "OR Format Error!" << endl;
        rules.push_back(e);
        getline(ifs, s);
    }
    cout << "Rules Size: " << rules.size() << endl;

    // Read Ticket
    //////////////
    while (s != "your ticket:") getline(ifs, s);
    getline(ifs, s);
    istringstream iss (s);
    string num;
    while(getline(iss, num, ',')) {
        your_ticket.push_back(stoi(num));  
    }
    cout << endl;

    // Read nearby ticket       
    /////////////////////
    while (s != "nearby tickets:") getline(ifs, s);
    getline(ifs, s);
    while (s.size()) {
        TICKET t;
        istringstream iss (s);
        string num;
        while(getline(iss, num, ',')) {
            t.push_back(stoi(num)); 
        }
        nearby_tickets.push_back(t);
        getline(ifs, s);
    }

    // Part1
    ////////
    int error_rate = 0;
    int ticket_index = 0;
    for (auto & t : nearby_tickets) {
        for (auto & num : t) {
            bool fits = false;
            for (auto & r : rules) {
                if ( ((num >= r.min1) && (num <= r.max1)) ||
                     ((num >= r.min2) && (num <= r.max2)) ) {
                     fits = true;
                     break;
                }
            }
            if (!fits) {
                error_tickets.push_back(ticket_index);
                error_rate += num;
            }
        }
        ticket_index++;
    }
    cout << "Error Rate: " << error_rate << endl;

    // Part 2
    /////////
    for (auto & r : rules) {
        for (int col = 0; col < nearby_tickets[0].size(); ++col) {
            bool fits = true;
            ticket_index = 0;
            for (auto & t : nearby_tickets) {
                if (std::find(error_tickets.begin(), 
                         error_tickets.end(),
                         ticket_index) != error_tickets.end()) {
                    ticket_index++;
                    continue;
                }
                int num = t[col];
                if ( ((num < r.min1) || (num > r.max1)) &&                 
                     ((num < r.min2) || (num > r.max2)) ) {
                     fits = false;
                     break;
                }
                ticket_index++;
            }
            if (fits) {
                r.fits.push_back(col);
            }
        }
    }
    // Reduce the fitting columns
    bool reduced;
    do {
        reduced = false;
        // Find single value
        for (int i=0; i < rules.size(); ++i) {
            if (rules[i].fits.size() == 1) {
                for (int j=0; j < rules.size(); ++j) {
                    if (j==i) continue;
                    auto pos = find(rules[j].fits.begin(),
                                    rules[j].fits.end(),
                                    rules[i].fits[0]);
                    if (pos != rules[j].fits.end()) {
                        rules[j].fits.erase(pos);
                        reduced = true;
                    }
                }        
            }
        }
    } while (reduced);

    // Calculate result
    ///////////////////
    long result = 1;
    for(auto & r : rules) {
        if (r.name.substr(0,9) == "departure") {
            result *= your_ticket[ r.fits[0] ];
        }
    }
    cout << result << endl;
}

