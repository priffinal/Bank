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
	double calculateInterest();
	bool withdraw(double amount);
	void deductFee();
	void createAccount();
	void displayInfo();
	CheckingAccount() : Account("", "", 0.0), overdraftLimit(0.0) {}
};