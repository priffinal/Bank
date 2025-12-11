#pragma once
#include "Transaction.h"
#include <ctime>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Account
{
protected:
	string accountID; 
	string customerID;
	tm *openDate;
	string status;
	long long balance;
	vector<Transaction> tr;
public:
	Account();
	Account(string id, string name, double initialBalance);
	virtual ~Account();

	virtual bool withdraw(double amount);
	virtual void deposit(double amount);
	// virtual bool transfer(double amount, string relatedID);
	virtual double calculateInterest();
	virtual void displayInfo();
	void printLog();
	long long getBalance();
	void lockAccount();
	void closeAccount();
	virtual void createAccount();
	void pushCusID(string ID);
};
