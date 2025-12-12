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
	CheckingAccount();
	double calculateInterest();
	bool withdraw(double amount);
	void deductFee();
	void createAccount(const Customer &c);
	void displayInfo();
	bool isSAV();
};