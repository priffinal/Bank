#include "SavingAccount.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

SavingAccount::SavingAccount() : Account("", "", 0.0)
{
	interest = 0;
	minimumBalance = 0.0;
	term = 0;
};

double SavingAccount::calculateInterest()
{
	 interest = minimumBalance*(4.67/100) * term ;
	 return interest;
}

void SavingAccount::displayInfo()
{
	cout << "\n--- Thong tin tai khoan tiet kiem ---" << endl;
	Account::displayInfo();
	cout << fixed << setprecision(2);
	cout << "\nLai suat: " << interestRate << "% /nam" << endl;
	cout << "\nSo du toi thieu: " << minimumBalance << endl;
	cout << "\nKy han: " << term << " nam" << endl;
}

void SavingAccount::createAccount()
{
	cout << "\n--- Tao tai khoan tiet kiem ---" << endl;
	Account::createAccount();
	cout << "\nNhap so du toi thieu: ";
	cin >> minimumBalance;
	cout << "\nNhap ky han (nam): ";
	cin >> term;
}
