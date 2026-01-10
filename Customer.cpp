#include"Customer.h"
#include"Account.h"
#include"CheckingAccount.h"
#include"SavingAccount.h"
#include "PrintTime.h"
#include<string>
#include<iostream>
#include <vector>
using namespace std;

//int Customer::n = 0;
Customer::Customer() {}
// tra ve thong tin ca nhan cua khach hang
string Customer::getID() { return customerID; }
string Customer::getName() { return fullName; }
string Customer::getAddress() { return address; }
string Customer::getEmail() { return email; }
string Customer::getPhone() { return phone; }

//ham them tai khoan
string Customer::addAccount(Account *acc)
{
	if (acc == nullptr) return "";
	acc->setOwner(this);
	account.push_back(acc);
	//n++;
	return acc->getID();
}

int Customer::getAccountCount() { return (int)account.size(); }

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
		 << " - So tai khoan: " << account.size() << endl;
}

//ham chinh sua tai khoan
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
	for (size_t i = 0; i < account.size(); i++)
	{
		if (account[i]->getID() == accID)
		{
			account.erase(account.begin() + i);
			return true;
		}
	}
	return false;
}

void Customer::list()
{
	for (int i = 0; i < account.size(); i++) {
		account[i]->printList();
	}
}

bool Customer::removeAllAccount()
{
	for (auto acc : account)
	{
		acc->closeAccount();
	}
	return true;
} 

void Customer::autoID(string ID)
{
	customerID = ID;
}

long long Customer::totalBalance()
{
	long long balance = 0;	
	for (auto acc : account) {
		balance += acc->getBalance();
	}
	return balance;
}