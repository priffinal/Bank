#define _CRT_SECURE_NO_WARNINGS
#include "Account.h"
#include "AutoGen.h"
#include "PrintTime.h"
#include "Customer.h"
#include "Transaction.h"
#include <iostream>
using namespace std;

map<string, int> Account::accType = {};
Account::Account(){}
Account::Account(double initialBalance)
{
	balance = initialBalance;	
	time_t now = time(0);
	tm ltm = *localtime(&now);
	openDate = ltm;
	status = "Open";
}

Account::~Account() {}

void Account::setOwner(Customer *c)
{
	customerInfo = c;
}

void Account::addTransaction(Transaction T) { tr.push_back(T); }

bool Account::withdraw(double amount)
{
	if (amount > balance) {
		return false;
	}
	else {
		balance -= amount;
		return true;
	}
}

void Account::deposit(double amount) { 
	balance += amount;
}

void Account::transfer_in(double amount, string relatedID) {
	balance += amount;
}

bool Account::transfer_out(double amount, string relatedID)
{
	if (amount > balance) {
		return false;
	} else {
		balance -= amount;
		return true;
	}
}

double Account::calculateInterest()
{
	return 0.0;
}

void Account::displayInfo()
{
	cout << "Account ID: " << accountID 
		 << " - Open Date: " << openDate 
		 << " - Status: " << status 
		 << " - Balance: " << balance << endl;
}

long long Account::getBalance() { return balance; }

void Account::closeAccount() { status = "Closed"; }

void Account::createAccount(const Customer &c, long long balance)
{
	this->balance = balance;
	
	time_t now = time(0);
	tm ltm = *localtime(&now);
	openDate = ltm;
	status = "Open";
}

string Account::getID() { return accountID; }

void Account::printList()
{
	cout << "ID: " << getID() << "So du: " << getBalance() << endl;
}
string Account::getopenDate()
{
	char buf[11]; 

	strftime(buf, sizeof(buf), "%Y-%m-%d", &openDate);

	return string(buf);

}