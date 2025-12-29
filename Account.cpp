#define _CRT_SECURE_NO_WARNINGS
#include "Account.h"
#include "AutoGen.h"
#include "PrintTime.h"
#include "Customer.h"
#include "Transaction.h"
#include <ctime>
#include <string>
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

bool Account::withdraw(double amount)
{
	if (amount > balance) {
		time_t now = time(0);
		tm ltm = *localtime(&now);
		tr.push_back(Transaction(accountID, "", ltm, amount, "withdraw", "failed"));
		return false;
	}
	else {
		balance -= amount;
		time_t now = time(0);
		tm ltm = *localtime(&now);
		tr.push_back(Transaction(accountID, "", ltm, amount, "withdraw", "success"));
		return true;
	}
}

void Account::deposit(double amount) { 
	balance += amount;
	time_t now = time(0);
	tm ltm = *localtime(&now);
	tr.push_back(Transaction(accountID, "", ltm, amount, "deposit", "success"));
}

void Account::transfer_in(double amount, string relatedID) {
	balance += amount;
	time_t now = time(0);
	tm ltm = *localtime(&now);
	tr.push_back(Transaction(accountID, "", ltm, amount, "transfer_in", "success"));
}

bool Account::transfer_out(double amount, string relatedID)
{
	if (amount > balance) {
		time_t now = time(0);
		tm ltm = *localtime(&now);
		tr.push_back(Transaction(accountID, "", ltm, amount, "transfer_out", "failed"));
		return false;
	} else {
		balance -= amount;
		time_t now = time(0);
		tm ltm = *localtime(&now);
		tr.push_back(Transaction(accountID, "", ltm, amount, "transfer_out", "success"));
		return true;
	}
}

double Account::calculateInterest()
{
	return 0.0;
}

void Account::displayInfo()
{
	cout << "- Account ID: " << accountID 
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