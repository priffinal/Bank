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
	void displayInfo();
	void createAccount();
	SavingAccount() : Account("", "", 0.0), interest(0), minimumBalance(0.0), term(0) {}
};