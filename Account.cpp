#define _CRT_SECURE_NO_WARNINGS
#include "Account.h"
#include "AutoGen.h"
#include "PrintTime.h"
#include "Customer.h"
#include "Transaction.h"
#include <iostream>
#include <algorithm>//for max
using namespace std;

map<string, int> Account::accType = {};
Account::Account(){}
Account::Account(double initialBalance)
{
	balance = initialBalance;	
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

void Account::openAccount() { status = "Open"; }

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
tm Account::getopenDate() { return openDate; }

string Account::getStatus() { return status; }

void Account::setID(string id) {
	this->accountID = id;
}

void Account::updateCounter(string type, int val) {
	if (val > accType[type]) {
		accType[type] = val;
	}
}