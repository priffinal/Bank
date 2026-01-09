#define _CRT_SECURE_NO_WARNINGS
#include "CheckingAccount.h"
#include "AutoGen.h"
#include "PrintTime.h"
#include "Customer.h"
#include <iostream>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;

CheckingAccount::CheckingAccount(long long balance, long long overdraftLimit, tm date) : Account(balance)
{
	this->overdraftLimit = overdraftLimit;
	this->accountID = autoGenerate("CHK", ++accType["checking"]);
	this->openDate = date;
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
	if (getBalance() < amount + transactionFee - overdraftLimit) return false;
	else {
		Account::withdraw(amount);
		return true;
	}
}

string CheckingAccount::toFileString() const {
    return "CHK|" + accountID + "|" + tmToString(openDate) + "|" + customerInfo->getID() + "|" +
           to_string(balance) + "|" +
           to_string(overdraftLimit);
}
