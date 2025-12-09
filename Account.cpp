#include "Account.h"
#include <ctime>
#include <string>
#include <iostream>
using namespace std;


Account::Account(){}
Account::Account(string id, string name, double initialBalance)
{
	accountID = id;
	customerID = name;
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
		tm *ltm = localtime(&now);
		tr.push_back(Transaction(accountID, "", ltm, amount, "withdraw", "failed"));
		return false;
	}
	balance -= amount;
	time_t now = time(0);
	tm *ltm = localtime(&now);
	tr.push_back(Transaction(accountID, "", ltm, amount, "withdraw", "success"));
	return true;
}

void Account::deposit(double amount)
{
	balance += amount;
	time_t now = time(0);
	tm *ltm = localtime(&now);
	tr.push_back(Transaction(accountID, "", ltm, amount, "deposit", "success"));
}

// bool Account::transfer(double amount, string relatedID)
// {
// 	if (amount > balance)
// 	{
// 		cout << "\nSo du khong du" << endl;
// 		tr.push_back(Transaction(accountID, relatedID, ctime(&now), amount, "transfer", "failed"));
// 		return false;
// 	}
// 	balance -= amount;
// 	//continue
// 	tr.push_back(Transaction(accountID, relatedID, ctime(&now), amount, "withdraw", "success"));
// 	return true;
// }


double Account::calculateInterest()
{
	return 0.0;
}

void Account::displayInfo()
{
	cout << "\nAccount ID: " << accountID << endl;
	cout << "\nCustomer ID: " << customerID << endl;
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

void Account::createAccount()
{
	cout << "\nNhap ID tai khoan: ";
	cin >> accountID;
	cout << "\nNhap ho va ten chu tai khoan: ";
	cin.ignore();
	getline(cin, customerID);
	cout << "\nNhap so du khoi tao: ";
	cin >> balance;
	openDate = "12-8-2024";
	status = "Open";
}

void Account::printLog()
{
	tr.at(0).log();
}

void Account::pushCusID(string ID)
{
	customerID = ID;
}