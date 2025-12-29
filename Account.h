#pragma once
#include "Transaction.h"
#include "AutoGen.h"
#include <map>
#include <ctime>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Customer;
class Transaction;

class Account
{
protected:
	string accountID;
	Customer *customerInfo;
	tm openDate;
	string status;
	long long balance;
	vector<Transaction> tr;
	static map<string, int> accType;
public:
	Account();
	Account(double initialBalance);
	~Account();
	virtual void createAccount(const Customer &c, long long balance);
	virtual void deposit(double amount);
	virtual void transfer_in(double amount, string relatedID);
	virtual bool transfer_out(double amount, string relatedID);
	virtual double calculateInterest();
	virtual void displayInfo();
	virtual void printList();
	long long getBalance();
	virtual bool withdraw(double amount) = 0;
	void setOwner(Customer *c);
	void lockAccount();
	void closeAccount();
	string getID();
};
