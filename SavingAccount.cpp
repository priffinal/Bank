#include "SavingAccount.h"
#include <iostream>
#include <iomanip>
using namespace std;

SavingAccount::SavingAccount(string id, string name, double initialBalance, double rate, int termVal) : Account(id, name, initialBalance), interestRate(rate), term(termVal), minimumBalance(50000) {}

double SavingAccount::calculateInterest()
{
    // Cong thuc: Lai = So du * (lai suat/100) * (ky han / 12)
    if (balance < minimumBalance) {return 0.0;}
    double interest = balance * (interestRate / 100.0) * ((double)term / 12.0);
    return interest;
}

void SavingAccount::applyInterest()
{
    double interest = calculateInterest();
    deposit(interest);
    cout << "Da cong lai suat: " << interest << " vao tai khoan." << endl;
}

void SavingAccount::displayInfo()
{
    Account::displayInfo();
    cout << "Type:       Saving Account" << endl;
    cout << "Interest Rate: " << interestRate << "%/nam" << endl;
    cout << "Term:       " << term << " thang" << endl;
}