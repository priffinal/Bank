#include"Customer.h"
#include"Account.h"
#include"CheckingAccount.h"
#include"SavingAccount.h"
#include<string>
#include<iostream>
using namespace std;

int Customer::n = 0;

Customer::Customer() {}

void Customer::autoID(string ID)
{
	customerID = ID;
}

string Customer::getID() {
	return customerID;
}

//ham them tai khoan
Account* Customer::addAccount()
{
	char choice;
	Account* lastCreated = nullptr;
	do 
	{
		cout << "Chon tai khoan tiet kiem hoac tai khoan thanh toan (1-TK/2-TT): ";
		cin >> choice;
		if (choice == '1') {
			account.push_back(new SavingAccount);
			account[n]->createAccount(*this);
			lastCreated = account[n++];
		}
		if (choice == '2') {
			account.push_back(new CheckingAccount);
			account[n]->createAccount(*this);
			lastCreated = account[n++];
		}
		cout << "Co tiep tuc khong (y/n): ";
		cin >> choice;
	} while (choice == 'y' || choice == 'Y');
	return lastCreated;
}

int Customer::getAccountCount() {
	return n;
}

Account* Customer::getAccountAt(int index) {
	if (index >= 0 && index < n) return account[index];
	return nullptr;
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
void Customer::showInfo()
{
	cout << "Ho ten: " << fullName << endl;
	cout << "ID: " << customerID << endl;
	cout << "Dien thoai: " << phone << endl;
	cout << "Email: " << email << endl;
	cout << "Dia chi: " << address << endl;
	cout << "So tai khoan: " << n << endl;
	for (int i = 0; i < n; i++) {
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