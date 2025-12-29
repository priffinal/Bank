#pragma once
#include "Account.h"
#include <string>
#include <iostream>
#include <iomanip>
class CheckingAccount : public Account
{
private:
	double transactionFee=10000;
	double overdraftLimit;
public:
	CheckingAccount(long long balance, long long overdraftLimit);
	double calculateInterest();
	bool withdraw(double amount);
	void createAccount(const Customer &c, long long balance);
	void displayInfo();
};