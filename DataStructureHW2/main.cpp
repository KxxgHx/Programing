#include <iostream>
#include <string>
#include <sstream>
#include "Bag.hpp"

using namespace std;

void show_state(const bag<int>& tree, const string& name) {
    cout << "\n=== Bag " << name << " ===" << endl;
    if (tree.empty()) {
        cout << "(empty)" << endl;
    } else {
        tree.show_contents(0);
    }
    cout << "==================" << endl;
}

int main() {
    bag<int> a;
    bag<int> b;

    cout << "B-Tree Bag Program (MINIMUM=1, MAXIMUM=2)\n" << endl;
    cout << "Commands: insert x, erase_one x, erase_all x, count x, assign_to b, show a/b, quit\n" << endl;
    
    string line, command;
    int value;
    
    while (true) {
        cout << "> ";

        getline(cin, line);
        if (line.empty()) continue;
        
        istringstream iss(line);
        iss >> command;
        
        for (char& c : command) c = tolower(c);
        
        if (command == "quit" || command == "q") {
            break;
        }
        else if (command == "insert") {
            if (iss >> value) {
                a.insert(value);
                cout << "Inserted " << value << endl;
                show_state(a, "A");
            } else {
                cout << "Usage: insert x" << endl;
            }
        }
        else if (command == "erase_one") {
            if (iss >> value) {
                bool success = a.erase_one(value);
                cout << (success ? "Erased one " : "Not found: ") << value << endl;
                show_state(a, "A");
            } else {
                cout << "Usage: erase_one x" << endl;
            }
        }
        else if (command == "erase_all") {
            if (iss >> value) {
                bool success = a.erase_all(value);
                cout << (success ? "Erased all " : "Not found: ") << value << endl;
                show_state(a, "A");
            } else {
                cout << "Usage: erase_all x" << endl;
            }
        }
        else if (command == "count") {
            if (iss >> value) {
                size_t cnt = a.count(value);
                cout << "Count of " << value << ": " << cnt << endl;
                show_state(a, "A");
            } else {
                cout << "Usage: count x" << endl;
            }
        }
        else if (command == "assign_to") {
            string target;
            if (iss >> target && (target == "b" || target == "B")) {
                b = a;
                cout << "Assigned A to B" << endl;
                show_state(a, "A");
                show_state(b, "B");
            } else {
                cout << "Usage: assign_to b" << endl;
            }
        }
        else if (command == "show") {
            string target;
            if (iss >> target) {
                if (target == "a" || target == "A") {
                    show_state(a, "A");
                } else if (target == "b" || target == "B") {
                    show_state(b, "B");
                }
            } else {
                show_state(a, "A");
                show_state(b, "B");
            }
        }
        else {
            cout << "Unknown command" << endl;
        }
    }

    return 0;
}
/*
insert 10
insert 5
insert 20
assign_to b

insert 10
insert 7
insert 5
assign_to b

insert 5
insert 15
insert 30
insert 2
assign_to b

insert 20
insert 25
insert 10
insert 1
insert 5

count 5
count 10
assign_to b

erase_one 5
erase_one 10
erase_one 100
assign_to b

erase_one 5
erase_one 20

erase_all 5
erase_all 10
assign_to b
erase_all 777
erase_all 20
erase_all 2

count 15
count 30
assign_to b

quit


*/