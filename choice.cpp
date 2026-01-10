#include "choice.h"
#include <iostream>
using namespace std;

int inputChoice(int min, int max) {
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail() || choice < min || choice > max) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Lua chon khong hop le. Nhap lai: ";
        }
        else {
            cin.ignore(1000, '\n');
            return choice;
        }
    }
}
