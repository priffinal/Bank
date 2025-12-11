#include <iostream>
#include "SavingAccount.h"
#include "CheckingAccount.h"
#include "Account.h"
#include <string>
using namespace std;

int main()
{
	int check;
	int n = 0;
	Account* tk[100];
	do
	{
		cout << "\nTao tai khoan thanh toan hay tai khoan tieu kiem? (1-TT, 2-TK): ";
		cin >> check;	
		if (check == 1)
		{
			tk[n] = new CheckingAccount;
			tk[n++]->createAccount();
		}
		else if (check == 2)
		{
			tk[n] = new SavingAccount;
			tk[n++]->createAccount();
		}
		cout << "\nTao them tai khoan khong? (1-Co, 0-Khong): ";
		cin >> check;
	} while (check == 1);

	tk[0]->displayInfo();
	return 0;
}