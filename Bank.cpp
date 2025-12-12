#include "Bank.h"
#include "AutoGen.h"
#include <iostream>
#include <ctime>
using namespace std;

int Bank::cusNum = 0;
int Bank::accNum = 0;

Bank::Bank(){}
Bank::~Bank(){}

void Bank::addCustomer()
{
    Customer c;
    c.createCustomer();
    c.autoID(autoGenerate("C", ++cusNum));
    customers.push_back(c);
}

Customer Bank::searchCustomer(string ID) {
    for (int i = 0; i < customers.size(); i++) {
        if (customers[i].getID() == ID) {
            return customers[i];
        }
    }
    throw runtime_error("Khong tim thay khach hang.");
}

void Bank::showCusInfo(string ID)
{
    searchCustomer(ID).showInfo();
}

void Bank::updateCusInfo(string ID)
{
    searchCustomer(ID).updateInfo();
}

void Bank::addAccount(string ID)
{
    Customer cust = searchCustomer(ID);
    Account *acc = cust.addAccount();
    if (acc) {
        accounts.push_back(acc);
    }
}

Account& Bank::searchAccount(string ID) {
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i]->getID() == ID) {
            return *accounts[i];
        }
    }
    throw runtime_error("Khong tim thay tai khoan.");
}

void Bank::deposit(Account &a, double amount)
{
    a.deposit(amount);
    time_t now = time(0);
    tm *ltm = localtime(&now);
    transactions.push_back(Transaction(a.getID(), "", ltm, amount, "deposit", "success"));
}

void Bank::withdraw(Account &a, double amount)
{
    a.withdraw(amount);
    time_t now = time(0);
    tm *ltm = localtime(&now);
    transactions.push_back(Transaction(a.getID(), "", ltm, amount, "withdraw", "success"));
}

void Bank::transfer(Account &a, string ID, double amount)
{
    if (a.transfer_out(amount, ID)) {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        transactions.push_back(Transaction(a.getID(), ID, ltm, amount, "transfer_out", "success"));
        searchAccount(ID).transfer_in(amount, a.getID());
        transactions.push_back(Transaction(ID, a.getID(), ltm, amount, "transfer_in", "success"));
    } else {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        transactions.push_back(Transaction(a.getID(), ID, ltm, amount, "transfer_out", "failed"));
    }
}

void Bank::deleteCustomer(string ID)
{
    for (int i = 0; i < customers.size(); i++) {
        if (customers[i].getID() == ID) {
            char choice;
            cout << "Ban co chac chan xoa nguoi dung khong (y/n): " << endl; cin >> choice;
            if (choice == 'y') {
                customers[i] = customers.back();
                customers.pop_back();
                cout << "Da xoa nguoi dung thanh cong.";
            } else {
                
            }
        }
    }
}