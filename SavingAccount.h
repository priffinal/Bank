#pragma once
#include "Account.h"
using namespace std;

class SavingAccount: public Account
{
private:
	long long interest;
	double interestRate;
	double minimumBalance;
	int term;
public:
    double calculateInterest();
	bool withdraw(double amount);
	void displayInfo();
	string toFileString() const;
	SavingAccount(long long balance, tm date, int term, float interestRate, string status);
};