#include "AccountMenu.h"
#include "CustomerMenu.h"
#include <iostream>

string checkAccount(Bank &bank)
{
    bool ok = false;
    string ID;
    do {
        cout << "Nhap ID tai khoan: "; cin >> ID;
        cin.ignore();
        if (bank.searchAccount(ID) == nullptr) {
            cout << "Khong the tim thay doi tuong. Vui long nhap lai.\n";
            ok = false;
        } 
        else ok = true;
    } while (!ok);
    return ID;
}

void openAccount(Bank &bank)
{
    int n;
    long long balance;
    string cusID = checkCustomer(bank), newID;
    cout << "Nhap loai tai khoan (1-TK / 2-TT): "; cin >> n;
    cout << "Nhap so du khoi tao: "; cin >> balance;
    if (n == 1) {
        newID = bank.addSAV(cusID, balance);
    } if (n == 2) {
        long long overdraftLimit;
        cout << "Nhap han muc thau chi: "; cin >> overdraftLimit;
        newID = bank.addCHK(cusID, balance, overdraftLimit);
    }
    cout << "Tao tai khoan thanh cong.\n";
    cout << "ID cua tai khoan la: " << newID << endl;
}

void closeAccount(Bank &bank)
{
    string accID = checkAccount(bank);
    bank.closeAccount(accID);
    cout << "Dong tai khoan thanh cong.\n";
}

void showAccInfo(Bank &bank)
{
    string accID = checkAccount(bank);
    bank.showAccInfo(accID);
}

void deposit(Bank &bank)
{
    string accID = checkAccount(bank);
    Account *acc = bank.searchAccount(accID);
    long long balance;
    cout << "Nhap so tien gui vao: "; cin >> balance;
    bank.deposit(*acc, balance);
    cout << "Chuyen thanh cong " << balance << " VND vao tai khoan.\n";
}

void withdraw(Bank &bank)
{
    string accID = checkAccount(bank);
    Account *acc = bank.searchAccount(accID);
    long long balance;
    cout << "Nhap so tien rut: "; cin >> balance;
    bool result = bank.withdraw(*acc, balance);
    if (result) cout << "Rut thanh cong " << balance << " VND.\n";
    else cout << "Rut that bai.\n";
}

void transfer(Bank &bank)
{
    bool ok = false;
    string accID, toID;
    do {
        cout << "Nhap ID tai khoan gui tien: "; cin >> accID;
        cin.ignore();
        cout << "Nhap ID tai khoan nhan tien: "; cin >> toID;
        cin.ignore();
        if (bank.searchAccount(accID) == nullptr || bank.searchAccount(toID) == nullptr) {
            cout << "Khach hang khong ton tai. Vui long nhap lai.\n";
            ok = false;
        }
        else ok = true;
    } while (!ok);
    Account *acc = bank.searchAccount(accID);
    long long balance;
    cout << "Nhap so tien gui vao: "; cin >> balance;
    bool result = bank.transfer(*acc, toID, balance);
    if (result) cout << "Chuyen thanh cong " << balance << "VND vao tai khoan cua " << toID <<".\n";
    else cout << "Chuyen tien that bai.\n";
}
void filterAccount(Bank& bank)
{
    int choice;
    do {
        cout << "\n===== QUAN LY LOC TAI KHOAN =====\n";
        cout << "1. Loc theo so du\n";
        cout << "2. Loc theo ID\n";
        cout << "3. Loc theo thoi gian\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        if (choice > 3 && choice < 0 && isalpha(choice)) {
            do {
                cout << "Khong hop le. Nhap lai: ";
                cin >> choice;
            } while (choice > 3 && choice < 0 && isalpha(choice));
        }

        switch (choice) {
        case 1:
            bank.filterAccountByBalance();
            break;
        case 2:
            bank.filterAccountByID();
            break;
        case 3:
            bank.filterAccountByDate();
            break;
        case 0:
            break;
        }
    } while (choice != 0);
}
void sortAccount(Bank& bank)
{
    int choice;
    do {
        cout << "\n===== QUAN LY SAP XEP TAI KHOAN =====\n";
        cout << "1. Sap xep theo so du\n";
        cout << "2. Sap xep theo ID\n";
        cout << "3. Sap xep theo thoi gian\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        if (choice > 3 && choice < 0 && isalpha(choice)) {
            do {
                cout << "Khong hop le. Nhap lai: ";
                cin >> choice;
            } while (choice > 3 && choice < 0 && isalpha(choice));
        }

        switch (choice) {
        case 1:
            bank.sortAccountBybalance();
            break;
        case 2:
            bank.sortAccountByID();
            break;
        case 3:
            bank.sortAccountByDate();
            break;
        case 0:
            break;
        }
    } while (choice != 0);
}