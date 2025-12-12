#include <iostream>
#include <string>
#include "Bank.h"
#include "SavingAccount.h"
#include "CheckingAccount.h"
#include "Account.h"
#include"Customer.h"
using namespace std;

int main() {
	Bank bank;
	bank.addCustomer();
	bank.addAccount("C0001");
}