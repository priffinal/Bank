#pragma once
#include "Account.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;
class SavingAccount:: public Account
{
private:
	double interestRate; // lai suat
	double minimumBalance; // so du toi thieu
	int term;//ky han
public:
	SavingAccount(); // ham tao mac dinh
	void calculateInterest(); // tinh lai suat

};
