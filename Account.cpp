#include "Account.h"
#include <string>
#include <iostream>
using namespace std;

Account::Account(string id, string name, double initialBalance) : accountID(id), customerID(name), balance(initialBalance), status("Open")
{
	// ham tao
}
Account::~Account() {}

bool Account::withdraw(double amount)
{
	if (amount > balance)
	{
		cout << "So du khong du" << endl;
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
	cout << "Account ID: " << accountID << endl;
	cout << "Customer ID: " << customerID << endl;
	cout << "Open Date: " << openDate << endl;
	cout << "Status: " << status << endl;
	cout << "Balance: " << balance << endl;
}
double Account::getBalance() const
{
	return balance;
}
void Account::closeAccount()
{
	status = "Closed";
}


