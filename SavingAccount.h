#pragma once
#include "Account.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;
class SavingAccount: public Account
{
private:
	long long interest; // so tien lai
	double interestRate=4.67; // lai suat
	double minimumBalance; // so du toi thieu
	int term;//ky han
public:
    double calculateInterest(); // tinh lai suat
	void displayInfo(); // hien thi thong tin tai khoan tiet kiem
	void createAccount(); // tao tai khoan tiet kiem
	SavingAccount() : Account("", "", 0.0), interest(0), minimumBalance(0.0), term(0) {} // ham tao mac dinh
};