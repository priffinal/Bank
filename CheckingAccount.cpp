#include "CheckingAccount.h"
#include <iostream>
#include <iomanip>
using namespace std;

CheckingAccount::CheckingAccount(string id, string name, double initialBalance, double limit) : Account(id, name, initialBalance), overdraftLimit(limit)
{}

double CheckingAccount::calculateInterest() {return 0.0;}

bool CheckingAccount::withdraw(double amount)
{
    double currentFee = 0;
    if (amount < 1000000) {currentFee = 1000;}
    else {currentFee = 5000;}

    double totalDeduction = amount + currentFee;

    if (totalDeduction > getBalance() + overdraftLimit)
    {
        cout << "Giao dich bi tu choi: Vuot qua han muc thau chi." << endl;
        cout << "(So tien can rut: " << amount << " + Phi: " << currentFee << ")" << endl;
        return false;
    }
    else
    {
        balance -= amount;      // Tru tien rut
        balance -= currentFee;  // Tru phi

        cout << fixed << setprecision(0);// cho dep
        cout << "Da rut: " << amount << " | Phi giao dich: " << currentFee << endl;
        cout << "So du moi: " << balance << endl;
        return true;
    }
}