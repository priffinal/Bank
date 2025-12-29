#pragma once
#include "Account.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class SavingAccount: public Account
{
private:
	long long interest;
	double interestRate=4.67;
	double minimumBalance;
	int term;
public:
    double calculateInterest();
	bool withdraw(double amount);
	void displayInfo();
	SavingAccount(long long balance);
};