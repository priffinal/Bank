#define _CRT_SECURE_NO_WARNINGS
#include "Bank.h"
#include "AutoGen.h"
#include"menu.h"
#include"Customer.h"
#include"SavingAccount.h"
#include"CheckingAccount.h"
#include <iostream>
#include <ctime>
using namespace std;

int Bank::cusNum = 0;
int Bank::accNum = 0;

Bank::Bank(){}
Bank::~Bank(){}

void Bank::addCustomer()
{
    ui.clearScreen();
    cout << "===== DANG KY KHACH HANG =====\n";
    Customer c;
    c.createCustomer();
    c.autoID(autoGenerate("C", ++cusNum));
    customers.push_back(c);
    cout << "Dang ky thanh cong!\n";
}

Customer* Bank::searchCustomer(string ID) {
   
    for (int i = 0; i < customers.size(); i++) {
        if (customers[i].getID() == ID) {
           return &customers[i];   // trả về địa chỉ
        }
    }
        return nullptr;
}

void Bank::showCusInfo(string ID)
{
    Customer* c = searchCustomer(ID);
    if (c != nullptr)
        c->showInfo();

}

void Bank::updateCusInfo(string ID)
{
    Customer* c = searchCustomer(ID);
    if (c != nullptr)
        c->updateInfo();

}

void Bank::addAccount() {
    ui.clearScreen();
    cout << "===== TAO TAI KHOAN =====\n";

    string customerID;
    cout << "Nhap ID khach hang: ";
    cin >> customerID;

    Customer* cust = searchCustomer(customerID);

    // ❌ Chưa đăng ký khách hàng
    if (cust == nullptr) {
        cout << "Khach hang chua dang ky!\n";
        cout << "Ban co muon dang ky khach hang moi? (y/n): ";

        char choice;
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            addCustomer();                // đăng ký khách hàng
            cust = searchCustomer(customerID); // tìm lại
        }
        else {
            cout << "Huy tao tai khoan!\n";
            system("pause");
            return;
        }
    }

    // ✅ Đã có khách hàng → tạo tài khoản
    cout << "\n1. Saving Account\n";
    cout << "2. Checking Account\n";
    cout << "Chon loai: ";
    int type;
    cin >> type;

    Account* acc = nullptr;
    if (type == 1) acc = new SavingAccount();
    else if (type == 2) acc = new CheckingAccount();
    else {
        cout << "Loai tai khoan khong hop le!\n";
        system("pause");
        return;
    }

    accounts.push_back(acc);
    cust->addAccount(acc);

    cout << "\nTao tai khoan thanh cong!\n";
    system("pause");
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

void Bank::run() {
    int choice;

    do {
        ui.showMainMenu();  
        cin >> choice;

        switch (choice) {
        case 1://QUAN LY TAI KHOAN
            accountmenu();
            break;
        case 2://GIAO DICH NGAN HANG
            transactionmenu();
            break;
        case 3://QUAN LY KHACH HANG
            customermenu();
            break;
        case 4://XEM DACH SACH

            break;
        case 5://Thoat

            break;
        }
    } while (choice != 0);
}
void Bank::accountmenu()
{
    int c;
    do
    {
        ui.ShowAccountMenu();
        cin >> c;
        switch (c) {
        case 1:  break;
        case 2:  break;
        case 3:  break;
        }

    } while (c != 0);
}
void Bank::customermenu()
{
    int p;
    do
    {
        ui.ShowCustomerMenu();
        cin >> p;
        switch (p) {
        case 1:  break;
        case 2:  break;
        case 3:  break;
        }

    } while (p != 0);
}
void Bank::transactionmenu() {
    int q;
    do
    {
        ui.ShowTransactionMenu();
        cin >> q;
        switch (q) {
        case 1:  break;
        case 2:  break;
        case 3:  break;
        }

    } while (q != 0);
}