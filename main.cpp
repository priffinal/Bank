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
	cout << "\nTao tai khoan thanh toan hay tai khoan tieu kiem? (1-TT, 2-TK): ";
	cin >> check;	
	do
	{
		if (check == 1)
		{
			tk[n] = new CheckingAccount();
			tk[n]->createAccount();
			n++;
		}
		else if (check == 2)
		{
			tk[n] = new SavingAccount();
			tk[n]->createAccount();
			n++;
		}
		cout << "\nTao them tai khoan khong? (1-Co, 0-Khong): ";
		cin >> check;
	} while (check == 1);

}