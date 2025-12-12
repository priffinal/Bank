#define _CRT_SECURE_NO_WARNINGS
#include "CheckingAccount.h"
#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;

CheckingAccount::CheckingAccount() : Account("", 0)
{
	overdraftLimit = 0.0;
}

bool CheckingAccount::isSAV() { return false; }

void CheckingAccount::createAccount(const Customer &c)
{
	cout << "\n--- Tao tai khoan thanh toan ---" << endl;
	Account::createAccount(c);
	cout << "\nNhap gioi han rut qua tai khoan: ";
	cin >> overdraftLimit;
}

void CheckingAccount::displayInfo()
{
	cout << "\n--- Thong tin tai khoan thanh toan ---" << endl;
	Account::displayInfo();
	cout << fixed << setprecision(2);
	cout << "\nPhi giao dich: " << transactionFee << endl;
	cout << "\nGioi han rut qua tai khoan: " << overdraftLimit <<"\n"<< endl;
}

void CheckingAccount::deductFee()
{
	if (getBalance() - transactionFee < overdraftLimit)
	{
		cout << "Giao dich bi tu choi do vuot qua han muc thau chi" << endl;
	}
	else
	{
		withdraw(transactionFee);
		cout << fixed << setprecision(2);
		cout << "Phi giao dich la " << transactionFee << "da tru" << endl;
	}
}

double CheckingAccount::calculateInterest()
{
	cout << "Tai khoan co lai suat thap" << endl;
	return 0.0;
}

bool CheckingAccount::withdraw(double amount)
{
	if (amount + transactionFee > getBalance() + overdraftLimit)
	{
		cout << "Rut tien bi tu choi do han muc khong du" << endl;
		time_t now = time(0);
		tm *ltm = localtime(&now);
		tr.push_back(Transaction(accountID, "", ltm, amount, "withdraw", "failed"));
		return false;
	}
	else
	{
		Account::withdraw(amount);
		deductFee();
		cout << fixed << setprecision(0);
		cout << "Da rut" << amount << "tu tai khoan" << endl;
		return true;
	}
}
