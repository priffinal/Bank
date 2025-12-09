#include <iostream>
#include "CheckingAccount.h"
#include <string>
#include <iomanip>
using namespace std;

CheckingAccount::CheckingAccount()
{
	Account("", "", 0.0);
	overdraftLimit = 0.0;
}

void CheckingAccount::createAccount()
{
	cout << "\n--- Tao tai khoan thanh toan ---" << endl;
	Account::createAccount();
	cout << "\nNhap gioi han rut qua tai khoan: ";
	cin >> overdraftLimit;
}

void CheckingAccount::displayInfo()
{
	cout << "\n--- Thong tin tai khoan thanh toan ---" << endl;
	Account::displayInfo();
	cout << fixed << setprecision(2);
	cout << "\nPhi giao dich: " << transactionFee << endl;
	cout << "\nGioi han rut qua tai khoan: " << overdraftLimit << endl;
}

void CheckingAccount::deductFee()
{
	if (getBalance() - transactionFee < overdraftLimit)
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

double CheckingAccount::calculateInterest()
{
	cout << "Tai khoan co lai suat thap" << endl;
	return 0.0;
}

bool CheckingAccount::withdraw(double amount)
{
	if (amount + transactionFee > getBalance() + overdraftLimit)
	{
		cout << "Rut tien bi tu choi do han muc khong du" << endl; return false;
	}
	else
	{
		Account::withdraw(amount);
		deductFee();
		cout << fixed << setprecision(2);
		cout << "Da rut" << amount << "tu tai khoan" << endl;
		return true;
	}
}
