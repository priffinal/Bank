#include "CheckingAccount.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;
void CheckingAccount::deductFee()
{
	if (getBalance() - transactionFee < -overdraftLimit)
	{
		cout << "Giao dich bi tu choi do vuot qua han muc thau chi" << endl;
	}
	else
	{
		withdraw(transactionFee);
		cout << fixed << setprecision(2);
		cout << "Phi giao dich la " << transactionFee << "da tru" << endl;
	}
}
void CheckingAccount::calculateInterest()
{
	cout << "Tai khoan co lai suat thap" << endl;
}
void CheckingAccount::withdraw(double amount)
{
	if (amount + transactionFee > getBalance() + overdraftLimit)
	{
		cout << "Rut tien bi tu choi do han muc khong du" << endl;
	}
	else
	{
		Account::withdraw(amount);
		deductFee();
		cout << fixed << setprecision(2);
		cout << "Da rut" << amount << "tu tai khoan" << endl;
	}
}


