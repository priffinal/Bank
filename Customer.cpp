#include"Customer.h"
#include"Account.h"
#include"CheckingAccount.h"
#include"SavingAccount.h"
#include<string>
#include<iostream>
using namespace std;
Customer::Customer() {}

string Customer::getID() {
	return customerID;
}
//ham them tai khoan
void Customer::addaccount()
{
	int choice;
	do {
		createcustomer();
		cout << "chon tai khoan tiet kiem hoac tai khoan thanh toan(1/2): ";
		cin >> choice;
		//createcustomer();
		if (choice == 1) {
			account[n] = new SavingAccount;
			
		}
		if (choice == 2) {
			account[n] = new CheckingAccount;
		}
		account[n++]->createAccount();
		//createcustomer();
		cout << "co tiep tuc k (y/n): ";
		cin >> choice;
	} while (choice == 'y');
}
double Customer::getBalance()
{
	double sum = 0;

	for (int i = 0; i < n; i++)
		sum += account[i]->getBalance();
	return sum;
}
void Customer::createcustomer()
{
	//cin.ignore();

	cout << "Nhap ho ten: ";
	getline(cin, fullName);
	cout<<"\n";
	cout << "Nhap so dien thoai: ";
	getline(cin, phone);
	cout << "\n";
	cout << "Nhap email: ";
	getline(cin, email);
	cout << "\n";
	cout << "Nhap dia chi: ";
	getline(cin, address);
	cout << "\n";
	//cin.ignore();
}


//ham show thong tin tai khoan
void Customer::showinfo()
{
	for (int i = 0; i <= n; i++) {
		cout << "Ho ten: " << fullName << "\n" << endl;
		cout << "Dien thoai: " << phone << "\n" << endl;
		cout << "Email: " << email << "\n" << endl;
		cout << "Dia chi: " << address << "\n" << endl;
		cout << "So tai khoan: " << n << "\n" << endl;
		account[i]->displayInfo();
	
	}
}

//ham chinh sua ti khoan
void Customer::updateInfo(string name, string p, string e, string addr)
{
	fullName = name;
	this->phone = p;
	this->address = addr;
	this->email = e;
}

//ham xoa tai khoan
bool Customer::removeAccount(string accID)
{
	for (int i = 0; i < n; i++)
	{
		if (account[i]->getID() == accID)
		{
			// Dịch trái các phần tử phía sau
			for (int j = i; j < n - 1; j++)
				account[j] = account[j + 1];
			n--;
			return true;
		}
	}
	return false;
}

