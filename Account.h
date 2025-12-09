#pragma once
#include <string>
#include <iostream>
using namespace std;
class Account
{
protected:
	string accountID; 
	string customerID;
	string openDate;
	string status;
	long long balance;
public:
	Account(string id, string name, double initialBalance);
	virtual ~Account();

	virtual bool withdraw(double amount);
	virtual void deposit(double amount);
	virtual double calculateInterest();
	virtual void displayInfo();
	long long getBalance();
	void closeAccount();
	void createAccount();
};