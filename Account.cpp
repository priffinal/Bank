#include "Account.h"
#include <iostream>
using namespace std;

Account::Account(string id, string name, double initialBalance, string date) : accountID(id), customerID(name), balance(initialBalance), openDate(date), status("Open")
{
}

Account::~Account() {}

bool Account::withdraw(double amount)
{
    if (amount > balance)
    {
        cout << "So du khong du de thuc hien giao dich co ban." << endl;
        return false;
    }
    balance -= amount;
    return true;
}

void Account::deposit(double amount)
{
    if (amount > 0) {
        balance += amount;
        cout << "Da gui " << amount << " vao tai khoan." << endl;
    }
}

double Account::calculateInterest()
{
    return 0.0; // Tai khoan thuong mac dinh khong co lai hoac lai = 0
}

void Account::displayInfo()
{
    cout << "-----------------------------------" << endl;
    cout << "Account ID: " << accountID << endl;
    cout << "Customer:   " << customerID << endl;
    cout << "Open Date:  " << openDate << endl;
    cout << "Status:     " << status << endl;
    cout << "Balance:    " << balance << endl;
}

double Account::getBalance() const
{
    return balance;
}

void Account::closeAccount()
{
    status = "Closed";
    balance = 0; // Rut het tien khi dong
    cout << "Tai khoan da dong." << endl;
}