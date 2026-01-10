#pragma once
#include "Account.h"
#include <string>
class CheckingAccount : public Account
{
private:
	double transactionFee=10000;
	double overdraftLimit;
public:
	CheckingAccount(long long balance, long long overdraftLimit, tm date, string status);
	double calculateInterest();
	bool withdraw(double amount);
	void displayInfo();
	string toFileString() const;
};