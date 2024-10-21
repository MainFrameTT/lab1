#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Pipe {
    string name;
    double length;
    double diameter;
    bool in_repair;

    Pipe() : name(""), length(0), diameter(0), in_repair(false) {}

    Pipe(string n, double l, double d, bool r) : name(n), length(l), diameter(d), in_repair(r) {}

    void print() {
        cout << "Name: " << name << endl;
        cout << "Length: " << length << " km" << endl;
        cout << "Diameter: " << diameter << " mm" << endl;
        cout << "Under repair: " << (in_repair ? "Yes" : "No") << endl;
    }

    void read() {
        cout << "Enter the name of the pipe: ";
        cin >> name;
        cout << "Enter the length of the pipe (in km): ";
        cin >> length;
        cout << "Enter the pipe diameter (in mm): ";
        cin >> diameter;
        cout << "Under repair? (1 - yes, 0 - no): ";
        int repair;
        cin >> repair;
        in_repair = (repair == 1);
    }

    void setRepair(bool r) {
        in_repair = r;
    }
};

