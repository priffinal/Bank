#pragma once
#include <string>
#include <iostream>
using namespace std;
class Account
{
protected:
	string accountID; //id tai khoan
	string customerID;// ten chu tai khoan
	string openDate;// ngay tao tai khoan
	string status;// trang thai tai khoan
	long long balance;// so du tai khoan

public:
	Account(string id, string name, double initialBalance);
	virtual ~Account();

	virtual bool withdraw(double amount);// rut tien
	virtual void deposit(double amount);// gui tien
	virtual double calculateInterest();// tinh lai suat
	virtual void displayInfo();// hien thi thong tin tai khoan
	long long getBalance();// lay so du tai khoan
	void closeAccount();// dong tai khoan
	void createAccount();// tao tai khoan
};