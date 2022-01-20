#include <iostream>
#include "LogicalScheme.h"
#include <string>

void clearValues(std::string& name, int* ids, int& id_cnt) {
    name = "";
    for (int i = 0; i < id_cnt; i++) {
        ids[i] = 0;
    }
    id_cnt = 0;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1, ' ');
    }
}

void clearValues(bool* values, int& val_cnt) {
    for (int i = 0; i < 5; i++) {
        values[i] = false;
    }
    val_cnt = 0;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(1, ' ');
    }
}

bool schemeFromConsole(std::string& name, int* ids, int& id_cnt) {
    clearValues(name, &ids[0], id_cnt);
    std::cin >> name;
    if (name == ";") {
        return false;
    }
    while (std::cin >> ids[id_cnt++]);
    return true;
}

void valuesFromConsole(bool* values, int& val_cnt) {
    clearValues(&values[0], val_cnt);
    while (std::cin >> values[val_cnt++]);
}

int main()
{
    LogicalScheme scheme;
    bool result = false;
    bool values[5];
    std::string name;
    int ids[10];
    int cnt;

    std::cout << "To stop entering elements enter ;\n" <<
        "Enter name and input elements (to stop enter any non-number symbol). " <<
        "For input values use 0..2\n";
    while (schemeFromConsole(name, &ids[0], cnt)) {
        scheme.append(name, &ids[0], cnt - 1);
    }
    while (1) {
        std::cout << "Enter input values (to stop enter any non-number symbol): ";
        valuesFromConsole(&values[0], cnt);
        try {
            result = scheme.calcValue(&values[0], cnt - 1);
            std::cout << "Result: " << result;
            break;
        }
        catch (ManyInsException e) {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}