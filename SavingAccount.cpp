#include "SavingAccount.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;
void SavingAccount::calculateInterest()
{
	double interest = minimumBalance * interestRate * term / 100; // cong thuc tinh lai suat
}

