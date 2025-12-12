#pragma once
#include "Transaction.h"
#include "Customer.h"
#include <map>
#include <ctime>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Account
{
protected:
	string accountID; 
	Customer customerInfo;
	tm *openDate;
	string status;
	long long balance;
	vector<Transaction> tr;
	static map<string, int> accType;
public:
	Account();
	Account(string id, double initialBalance);
	~Account();

	bool withdraw(double amount);
	virtual bool isSAV()=0;
	virtual void deposit(double amount);
	virtual void transfer_in(double amount, string relatedID);
	virtual bool transfer_out(double amount, string relatedID);
	virtual double calculateInterest();
	virtual void displayInfo();
	void printLog();
	long long getBalance();
	void lockAccount();
	void closeAccount();
	virtual void createAccount(const Customer &c);
	void pushCusID(string ID);
	string getID();
};
