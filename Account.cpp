#include "Account.h"
#include <string>
#include <iostream>
using namespace std;

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
		return false;
	}
	balance -= amount;
	return true;
}

void Account::deposit(double amount)
{
	balance += amount;
}

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
	openDate = "2024-12-08";
	status = "Open";
}
void Account::pushCusID(string ID)
{
	customerID = ID;
}
