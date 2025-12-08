#pragma once
#include "Account.h"
#include <string>
#include <iostream>
#include <iomanip>
class CheckingAccount : public Account
{
private:
	double transactionFee; // phi giao dich
	double overdraftLimit; // gioi han rut qua tai khoan
public:
	double calculateInterest(); // tinh lai suat (lai suat nho)
	bool withdraw(double amount); // rut tien voi phi giao dich va gioi han rut qua tai khoan
};

