#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

int safeIntInput(string promt) {
    int value;
    while (true) {
        cout << promt;
        cin >> value;
        if (cin.fail() || value < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите положительное, целое число" << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n' );
            return value;
        }
    }
}

int safeDoubleInput(string promt) {
    double value;
    while (true) {
        cout << promt;
        cin >> value;
        if (cin.fail() || value < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите положительное, целое число" << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n' );
            return value;
        }
    }
}


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

struct CompressorStation {
    string name;
    int num_shops;
    int working_shops;
    double efficiency;

    CompressorStation() : name(""), num_shops(0), working_shops(0), efficiency(0) {}

    void print() {
        cout << "Название КС: " << name << endl;
        cout << "Количество цехов: " << num_shops << endl;
        cout << "Цехов в работе: " << working_shops << endl;
        cout << "Эффективность: " << efficiency << endl;
    }

    void read() {
        cout << "Введите название КС: ";
        getline(cin, name);
        num_shops = safeIntInput("Введите количество цехов: ");
        working_shops = safeIntInput("Введите количество работающих цехов: ");
        while (working_shops > num_shops) {
            cout << "Ошибка: количество работающих цехов не может превышать общее количество цехов!" << endl;
            working_shops = safeIntInput("Введите количество работающих цехов: ");
        }
        efficiency = safeDoubleInput("Введите эффективность КС: ");
    }

    void startShop() {
        if (working_shops < num_shops) {
            working_shops++;
            cout << "Цех запущен!" << endl;
        } else {
            cout << "Все цеха уже работают!" << endl;
        }
    }

    void stopShop() {
        if (working_shops > 0) {
            working_shops--;
            cout << "Цех остановлен!" << endl;
        } else {
            cout << "Все цеха уже остановлены!" << endl;
        }
    }
};

Pipe pipe;
CompressorStation compressorStation;

void loadData(string filename) {
    ifstream infile(filename);
    if (infile.is_open()) {
        string line;
        string type;
        while (getline(infile, line)) {
            if (line.find("Pipe:") != string::npos) {
                type = "Pipe";
                continue;
            } else if (line.find("CompressorStation:") != string::npos) {
                type = "CompressorStation";
                continue;
            }

            if (type == "Pipe") {
                string name, lengthStr, diameterStr, repairStr;
                int commaIndex = line.find(',');
                name = line.substr(0, commaIndex);
                line = line.substr(commaIndex + 1);
                commaIndex = line.find(',');
                lengthStr = line.substr(0, commaIndex);
                line = line.substr(commaIndex + 1);
                commaIndex = line.find(',');
                diameterStr = line.substr(0, commaIndex);
                repairStr = line.substr(commaIndex + 1);

                pipe = Pipe(name, stod(lengthStr), stod(diameterStr), repairStr == "1");
            } else if (type == "CompressorStation") {
                string name, numShopsStr, workingShopsStr, efficiencyStr;
                int commaIndex = line.find(',');
                name = line.substr(0, commaIndex);
                line = line.substr(commaIndex + 1);
                commaIndex = line.find(',');
                numShopsStr = line.substr(0, commaIndex);
                line = line.substr(commaIndex + 1);
                commaIndex = line.find(',');
                workingShopsStr = line.substr(0, commaIndex);
                efficiencyStr = line.substr(commaIndex + 1);

                compressorStation = CompressorStation(name, stoi(numShopsStr), stoi(workingShopsStr), stod(efficiencyStr));
            }
        }
        infile.close();
        cout << "Данные загружены из файла " << filename << endl;
    } else {
        cout << "Ошибка при открытии файла!" << endl;
    }
}

