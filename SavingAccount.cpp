#define _CRT_SECURE_NO_WARNINGS
#include "SavingAccount.h"
#include <string>
#include <ctime>
#include <iostream>
#include <iomanip>
using namespace std;

tm addYears(tm *t, int year)
{
	t->tm_year += year;
	time_t time = mktime(t);
	return *localtime(&time);
}

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
	cout << "\nKy han: " << term << " nam" <<"\n"<< endl;
}

void SavingAccount::createAccount()
{
	cout << "\n--- Tao tai khoan tiet kiem ---" << endl;
	Account::createAccount();
	cout << "\nNhap so du toi thieu: ";
	cin >> minimumBalance;
	cout << "\nNhap ky han (nam): "<<"\n";
	cin >> term;
}

bool SavingAccount::withdraw(double amount)
{
	time_t now = time(0);
	tm expiredTm = addYears(openDate, term);
	time_t expired = mktime(&expiredTm);
	if (difftime(expired, now)>0) {
		cout << "Khong ho tro rut tien trong ky han.";
		tr.push_back(Transaction(accountID, "", localtime(&now), amount, "withdraw", "failed"));
		return 0;
	}
	else
	{
		Account::withdraw(amount);
		cout << fixed << setprecision(0);
		cout << "Da rut" << amount << "tu tai khoan" << endl;
		return true;
	}
}