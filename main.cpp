#include <iostream> //ввод/вывод
#include <fstream> //работа с файлами
#include <string> //работа со строками
#include <limits> //пределы типов данных

using namespace std; //пространство имен

//проверка
int safeIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите положительное целое число." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

//проверка
double safeDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите положительное число." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

//Определение трубы
struct Pipe {
    string name;
    double length;
    double diameter;
    bool in_repair;

    Pipe() : name(""), length(0), diameter(0), in_repair(false) {}

    Pipe(string n, double l, double d, bool r) : name(n), length(l), diameter(d), in_repair(r) {}

    void print() {
        cout << "Название: " << name << endl;
        cout << "Длина: " << length << " km" << endl;
        cout << "Диаметр: " << diameter << " mm" << endl;
        cout << "В ремонте: " << (in_repair ? "Да" : "Нет") << endl;
    }

    void read() {
        cout << "Введите название трубы: ";
        getline(cin, name);
        length = safeDoubleInput("Введите длину трубы (в км): ");
        diameter = safeDoubleInput("Введите диаметр трубы (в мм): ");
        in_repair = safeIntInput("В ремонте? (1 - да, 0 - нет): ") == 1;
    }

    void setRepair(bool r) {
        in_repair = r;
    }
};

//Определение КС
struct CompressorStation {
    string name;
    int num_shops;
    int working_shops;
    double efficiency;

    CompressorStation() : name(""), num_shops(0), working_shops(0), efficiency(0) {}

    CompressorStation(string n, int shops, int working, double eff)
        : name(n), num_shops(shops), working_shops(working), efficiency(eff) {}

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

//Объявление глобальных переменных
Pipe pipe;
CompressorStation compressorStation;

//Сохранение данных в файл
void saveData(const string& filename) {
    ofstream outfile(filename);
    if (outfile.is_open()) {
        outfile << "Pipe:" << endl;
        outfile << pipe.name << "," << pipe.length << "," << pipe.diameter << "," << (pipe.in_repair ? "1" : "0") << endl;

        outfile << "CompressorStation:" << endl;
        outfile << compressorStation.name << "," << compressorStation.num_shops << "," << compressorStation.working_shops << "," << compressorStation.efficiency << endl;
        outfile.close();
        cout << "Данные сохранены в файл " << filename << endl;
    } else {
        cout << "Ошибка при открытии файла!" << endl;
    }
}

//Загрузка данных из файла
void loadData(const string& filename) {
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

//Отображение меню
void showMenu() {
    cout << "Меню:" << endl;
    cout << "1. Добавить трубу" << endl;
    cout << "2. Добавить КС" << endl;
    cout << "3. Просмотреть все объекты" << endl;
    cout << "4. Редактировать трубу" << endl;
    cout << "5. Редактировать КС" << endl;
    cout << "6. Сохранить" << endl;
    cout << "7. Загрузить" << endl;
    cout << "0. Выход" << endl;
    cout << "Введите ваш выбор: ";
}

//Обработка выбора пользователя
void handleChoice() {
    int choice = safeIntInput("");
    switch (choice) {
    case 1:
        pipe.read();
        cout << "Труба добавлена!" << endl;
        break;
    case 2:
        compressorStation.read();
        cout << "КС добавлена!" << endl;
        break;
    case 3:
        cout << "---- Труба ----" << endl;
        pipe.print();
        cout << "---- КС ----" << endl;
        compressorStation.print();
        break;
    case 4:
        pipe.setRepair(safeIntInput("В ремонте? (1 - да, 0 - нет): ") == 1);
        cout << "Труба обновлена!" << endl;
        break;
    case 5: {
        int action = safeIntInput("1. Запустить цех\n2. Остановить цех\nВведите действие: ");
        if (action == 1) {
            compressorStation.startShop();
        } else if (action == 2) {
            compressorStation.stopShop();
        } else {
            cout << "Неправильный выбор!" << endl;
        }
        break;
    }
    case 6:
        saveData("data.txt");
        break;
    case 7:
        loadData("data.txt");
        break;
    case 0:
        cout << "Выход из программы..." << endl;
        exit(0);
    default:
        cout << "Неправильный выбор!" << endl;
        break;
    }
}

//Инициализация
int main() {
    while (true) {
        showMenu();
        handleChoice();
    }
}