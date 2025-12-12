#define _CRT_SECURE_NO_WARNINGS
#include "Account.h"
#include "AutoGen.h"
#include "PrintTime.h"
#include <ctime>
#include <string>
#include <iostream>
using namespace std;

map<string, int> Account::accType = {};
Account::Account(){}
Account::Account(string id, double initialBalance)
{
	accountID = id;
	balance = initialBalance;
	status = "Open";
}

Account::~Account() {}

bool Account::withdraw(double amount)
{
	if (amount > balance)
	{
		cout << "\nSo du khong du" << endl;
		time_t now = time(0);
		tm* ltm = localtime(&now);
		tr.push_back(Transaction(accountID, "", ltm, amount, "withdraw", "failed"));
		return false;
	}
	balance -= amount;
	time_t now = time(0);
	tm* ltm = localtime(&now);
	tr.push_back(Transaction(accountID, "", ltm, amount, "withdraw", "success"));
	return true;
}

void Account::deposit(double amount)
{
	balance += amount;
	time_t now = time(0);
	tm* ltm = localtime(&now);
	tr.push_back(Transaction(accountID, "", ltm, amount, "deposit", "success"));
}

void Account::transfer_in(double amount, string relatedID)
{
	balance += amount;
	time_t now = time(0);
	tm* ltm = localtime(&now);
	tr.push_back(Transaction(accountID, relatedID, ltm, amount, "transfer_in", "success"));
}

bool Account::transfer_out(double amount, string relatedID)
{
	if (amount > balance)
	{
		cout << "\nSo du khong du" << endl;
		time_t now = time(0);
	tm* ltm = localtime(&now);
		tr.push_back(Transaction(accountID, relatedID, ltm, amount, "transfer_out", "failed"));
	}
	balance -= amount;
	time_t now = time(0);
	tm* ltm = localtime(&now);
	tr.push_back(Transaction(accountID, relatedID, ltm, amount, "transfer_out", "success"));
	return true;
}

double Account::calculateInterest()
{
	return 0.0;
}

void Account::displayInfo()
{
	cout << "\nAccount ID: " << accountID << endl;
	cout << "\nOpen Date: " << openDate << endl;
	cout << "\nStatus: " << status << endl;
	cout << "\nBalance: " << balance << endl;
}

long long Account::getBalance()
{
	return balance;
}

void Account::closeAccount()
{
	status = "Closed";
}

void Account::createAccount(const Customer &c)
{
	cout << "\nNhap so du khoi tao: ";
	cin >> balance;
	if (isSAV()) {
		accountID = autoGenerate("SAV", ++accType["saving"]);
	} else accountID = autoGenerate("CHK", ++accType["checking"]);
	time_t now = time(0);
	tm *ltm = localtime(&now);
	openDate = ltm;
	customerInfo = c;
	status = "Open";

}

void Account::printLog()
{
	tr.at(0).log();
}

string Account::getID()
{
	return accountID;
}