#include "CheckingAccount.h"
#include <iostream>
#include <iomanip>
using namespace std;

CheckingAccount::CheckingAccount(string id, string name, double initialBalance, double fee, double limit) : Account(id, name, initialBalance), transactionFee(fee), overdraftLimit(limit)
{}

double CheckingAccount::calculateInterest()
{
    // Checking account thuong khong co lai suat hoac lai suat rat thap
    return 0.0;
}

bool CheckingAccount::withdraw(double amount)
{
    // Tong tien can tru = so tien rut + phi giao dich
    double totalDeduction = amount + transactionFee;

    // Kiem tra kha nang chi tra (so du hien tai + han muc thau chi)
    if (totalDeduction > getBalance() + overdraftLimit)
    {
        cout << "Giao dich bi tu choi: Vuot qua han muc thau chi." << endl;
        return false;
    }
    else
    {
        // Tru tien rut
        // Luu y: Goi Account::withdraw de tru truc tiep vao balance ma khong goi lai CheckingAccount::withdraw
        if (getBalance() >= amount) {
            Account::withdraw(amount);
        }
        else {
            // Truong hop so du < amount nhung van trong han muc thau chi -> balance se am
            balance -= amount; // Tru truc tiep bien balance vi la class con
        }

        // Tru phi giao dich
        balance -= transactionFee;

        cout << fixed << setprecision(2);
        cout << "Da rut: " << amount << ". Phi giao dich: " << transactionFee << endl;
        cout << "So du moi: " << balance << endl;
        return true;
    }
}