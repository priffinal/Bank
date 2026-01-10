#define _CRT_SECURE_NO_WARNINGS
#include "SavingAccount.h"
#include "AutoGen.h"
#include "PrintTime.h"
#include "Customer.h"
#include <string>
#include <ctime>
#include <iostream>
#include <iomanip>
using namespace std;


tm addYears(tm t, int year)
{
	t.tm_year += year;
	time_t time = mktime(&t);
	return *localtime(&time);
}

SavingAccount::SavingAccount(long long balance, tm date) : Account(balance)
{
	interest = 0;
	minimumBalance = 0.0;
	term = 0;
	accountID = autoGenerate("SAV", ++accType["saving"]);
	openDate = date;
	interestRate = 4.67;
};

double SavingAccount::calculateInterest()
{
	interest = balance * (interestRate / 100.0) * term;
	 return interest;
}

void SavingAccount::displayInfo()
{
	cout << "\n--- Thong tin tai khoan tiet kiem ---" << endl;
	Account::displayInfo();
	cout << fixed << setprecision(2);
	cout << "\nLai suat: " << interestRate << "% /nam" << endl;
	cout << "\nSo du toi thieu: " << minimumBalance << endl;
	cout << "\nKy han: " << term << " nam" <<"\n"<< endl;
}

bool SavingAccount::withdraw(double amount)
{
	time_t now = time(0);
	tm expiredTm = addYears(openDate, term);
	time_t expired = mktime(&expiredTm);
	if (difftime(expired, now) > 0) return false;
	else return Account::withdraw(amount);
}

string SavingAccount::toFileString() const {
	return "SAV|" + accountID + "|" +
		tmToString(openDate) + "|" +
		customerInfo->getID() + "|" +
		to_string(balance) + "|" +
		to_string(interestRate) + "|" +
		to_string(term) + "|" +
		to_string(minimumBalance);
}
