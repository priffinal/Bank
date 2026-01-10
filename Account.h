#pragma once
#include <map>
#include <ctime>
#include <string>
#include <vector>
using namespace std;

class Customer;
class Transaction;

class Account
{
protected:
	string accountID;
	Customer *customerInfo;
	tm openDate;
	string status;
	long long balance;
	vector<Transaction> tr;
	static map<string, int> accType;
public:
	Account();
	Account(double initialBalance);
	~Account();
	virtual void createAccount(const Customer &c, long long balance);
	virtual string toFileString() const = 0;
	virtual void deposit(double amount);
	virtual void transfer_in(double amount, string relatedID);
	virtual bool transfer_out(double amount, string relatedID);
	virtual double calculateInterest();
	virtual void displayInfo();
	virtual void printList();
	virtual bool withdraw(double amount) = 0;
	void addTransaction(Transaction T);
	long long getBalance();
	void setOwner(Customer *c);
	void closeAccount();
	void openAccount();
	string getID();
	tm getopenDate();
	string getStatus();
	// De cap nhat ID khi load file
	void setID(string id);
	static void updateCounter(string type, int val);
};
