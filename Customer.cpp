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
string Customer::addAccount(Account *acc)
{
	if (acc == nullptr) return "";
	acc->setOwner(this);
	account.push_back(acc);
	n++;
	return acc->getID();
}

int Customer::getAccountCount() { return n; }

Account* Customer::searchAccount(string ID) 
{
	for (int i = 0; i < account.size(); i++) {
		if (account[i]->getID() == ID) return account[i];
	}
	return nullptr;
}

void Customer::createCustomer(string name, string phone, string email, string address)
{
	this->fullName = name;
	this->phone = phone;
	this->email = email;
	this->address = address;
}
void Customer::showInfo()
{
	cout << "Ho ten: " << fullName 
		 << " - ID: " << customerID 
		 << " - Dien thoai: " << phone 
		 << " - Email: " << email 
		 << " - Dia chi: " << address 
		 << " - So tai khoan: " << n << endl;
}

//ham chinh sua ti khoan
void Customer::updateInfo(string name, string phone, string email, string address)
{	
	if (!name.empty()) fullName = name;
	if (!phone.empty())	this->phone = phone;
	if (!address.empty()) this->address = address;
	if (!email.empty())	this->email = email;
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

void Customer::list()
{
	for (int i = 0; i <= n; i++) {
		account[i]->printList();
	}
}

bool Customer::removeAllAccount()
{

	for (int i = 0; i < n; i++)
	{
		account[i]->closeAccount();
	}
	return true;
} 

void Customer::autoID(string ID)
{
	customerID = ID;
}