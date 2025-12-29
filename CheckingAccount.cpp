#define _CRT_SECURE_NO_WARNINGS
#include "CheckingAccount.h"
#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;

CheckingAccount::CheckingAccount(long long balance, long long overdraftLimit) : Account(balance)
{
	this->overdraftLimit = overdraftLimit;
	this->accountID = autoGenerate("CHK", ++accType["checking"]);
}


void CheckingAccount::createAccount(const Customer &c, long long balance)
{
	cout << "\n--- Tao tai khoan thanh toan ---" << endl;
	Account::createAccount(c, balance);
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

double CheckingAccount::calculateInterest()
{
	cout << "Tai khoan co lai suat thap" << endl;
	return 0.0;
}

bool CheckingAccount::withdraw(double amount)
{
	if (getBalance() < amount + transactionFee - overdraftLimit)
	{
		time_t now = time(0);
		tm ltm = *localtime(&now);
		tr.push_back(Transaction(accountID, "", ltm, amount, "withdraw", "failed"));
		return false;
	}
	else
	{
		Account::withdraw(amount);
		return true;
	}
}
