#include <iostream>
#include "LogicalScheme.h"
#include <string>
#include <ctime>

void clearValues(std::string& name, int* in_ids, int& in_id_cnt, int* out_ids, int& out_id_cnt) {
    name = "";
    for (int i = 0; i < in_id_cnt; i++) {
        in_ids[i] = 0;
    }
    in_id_cnt = 0;
    for (int i = 0; i < out_id_cnt; i++) {
        out_ids[i] = 0;
    }
    out_id_cnt = 0;
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

bool schemeFromConsole(std::string& name, int* in_ids, int& in_id_cnt, int* out_ids, int& out_id_cnt) {
    clearValues(name, &in_ids[0], in_id_cnt, &out_ids[0], out_id_cnt);
    std::cin >> name;
    if (name == ";") {
        return false;
    }
    std::string str;
    while (1) {
        std::cin >> str;
        try {
            int id = std::stoi(str);
            in_ids[in_id_cnt++] = id;
        }
        catch (std::invalid_argument e) {
            break;
        }
    }
    
    if (str == "+") {
        while (std::cin >> out_ids[out_id_cnt++]);
    }
    return true;
}

void valuesFromConsole(bool* values, int& val_cnt) {
    clearValues(&values[0], val_cnt);
    while (std::cin >> values[val_cnt++]);
}

void genValues(bool* values, int& val_cnt) {
    clearValues(&values[0], val_cnt);
    val_cnt = 2 + rand() % 2;
    for (int i = 0; i < val_cnt; i++) {
        values[i] = (bool)(rand() % 2);
        std::cout << values[i] << " ";
    }
    std::cout << '\n';
}

int main()
{
    srand(time(0));
    LogicalScheme scheme;
    bool result = false;
    bool values[5];
    std::string name;
    int in_ids[10];
    int in_cnt;
    int out_ids[10];
    int out_cnt;
    int cnt;
    /*
    генератор значений:
    genValues(&values[0], cnt);
    */
    std::cout << "To stop entering elements enter ;\n" <<
        "Enter name and input elements (to stop enter any non-number symbol). " <<
        "For input values use 0..2\n";
    
    while (schemeFromConsole(name, &in_ids[0], in_cnt, &out_ids[0], out_cnt)) {
        if (out_cnt == 0) {
            scheme.append(name, &in_ids[0], in_cnt);
        }
        else {
            scheme.append(name, &in_ids[0], in_cnt, &out_ids[0], out_cnt - 1);
        }
    }
    scheme.remove(5);
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

/*
and 0 1 ;
not 2 ;
or 1 2 + 4 ;
xor 3 5 ;
;
*/