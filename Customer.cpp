#include"Customer.h"
#include"Account.h"
#include"CheckingAccount.h"
#include"SavingAccount.h"
#include<string>
#include<iostream>
using namespace std;

int Customer::n = 0;

Customer::Customer() {}

string Customer::getID() {
	return customerID;
}

//ham them tai khoan
void Customer::addAccount()
{
	int choice;
	do {
		createCustomer();
		cout << "Chon tai khoan tiet kiem hoac tai khoan thanh toan (1-TK/2-TT): ";
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
		cout << "Co tiep tuc k (y/n): ";
		cin >> choice;
	} while (choice == 'y');
}

void Customer::createCustomer()
{
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
}


//ham show thong tin tai khoan
void Customer::showinfo()
{
	for (int i = 0; i < n; i++) {
		cout << "Ho ten: " << fullName << "\n" << endl;
		cout << "Dien thoai: " << phone << "\n" << endl;
		cout << "Email: " << email << "\n" << endl;
		cout << "Dia chi: " << address << "\n" << endl;
		cout << "So tai khoan: " << n << "\n" << endl;
		account[i]->displayInfo();
	}
}

//ham chinh sua ti khoan
void Customer::updateInfo()
{	
	string name, p, e, addr;
	cout << "Sua thong tin (khong can sua thi an Enter): " << endl;
	cout << "Nhap ten: "; getline(cin, name);
	cout << "Nhap SDT: "; cin >> p;
	cout << "Nhap email: "; cin >> e;
	cout << "Nhap dia chi: "; getline(cin, addr);

	if (!name.empty()) fullName = name;
	if (!p.empty())	this->phone = p;
	if (!addr.empty()) this->address = addr;
	if (!e.empty())	this->email = e;
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