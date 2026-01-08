#include "Menu.h"
#include "CustomerMenu.h"
#include "AccountMenu.h"
#include "TransactionMenu.h"
#include <iostream>
#include <iomanip>
#include <string>

Menu::Menu(Bank &b) : bank(b) {}
Menu::~Menu() {}

void Menu::mainMenu()
{
    int choice;
    do {
        cout << "\n===== QUAN LY NGAN HANG =====\n";
        cout << "1. Quan ly khach hang\n";
        cout << "2. Quan ly tai khoan\n";
        cout << "3. Giao dich\n";
        cout << "4. Thong ke\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        if (choice > 4 && choice < 0 && isalpha(choice)) {
            do {
                cout << "Khong hop le. Nhap lai: "; 
                cin >> choice;
            } while (choice > 4 && choice < 0 && isalpha(choice));
        }

        switch (choice) {
        case 1:
            customerMenu();
            break;
        case 2:
            accountMenu();
            break;
        case 3:
            transactionMenu();
            break;
        case 4:
            statisticsMenu(bank);
            break;
        case 0:
            break;
        }
    } while (choice != 0);
}

void Menu::customerMenu()
{
    int choice;
    do {
        cout << "\n----- QUAN LY KHACH HANG ----\n";
        cout << "1. Them khach hang\n";
        cout << "2. Sua thong tin\n";
        cout << "3. Hien thong tin\n";
        cout << "4. Xoa khach hang\n";
        cout << "5. Sap xep khach hang\n";
        cout << "6. Thong ke khach hang\n";
        cout << "0. Quay lai\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();
        cout << "\n";

        switch (choice) {
        case 1:	{
            addCustomer(bank);
            break;
        }
        case 2: {
            editCusInfo(bank);
            break;
        }
        case 3: {
            showCusInfo(bank);
            break;
        }
        case 4: {
            deleteCustomer(bank);
            break;
        }case 5: {
            bank.sortCustomer();
            break;
        }case 6: {
            bank.statCustomer();
            break;
        }
        case 0:
            break;
        }
    } while (choice != 0);
}

void Menu::accountMenu()
{
    int choice;
    do {
        bool ok = false;
        cout << "\n----- QUAN LY TAI KHOAN ----\n";
        cout << "1. Mo tai khoan\n";
        cout << "2. Dong tai khoan\n";
        cout << "3. Hien thong tin\n";
        cout << "4. Gui tien\n";
        cout << "5. Rut tien\n";
        cout << "6. Chuyen tien\n";
        cout << "7. Sap xep tai khoan\n";
        cout << "8. Thong ke tai khoan\n";
        cout << "0. Quay lai\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();
        cout << "\n";

        switch (choice) {
            case 1: {
                openAccount(bank);
                break;
            } case 2: {
                closeAccount(bank);
                break;
            } case 3: {
                showAccInfo(bank);
                break;
            } case 4: {
                deposit(bank);
                break;
            } case 5: {
                withdraw(bank);
                break;
            } case 6: {
                transfer(bank);
                break;
            }  case 7: {
                bank.sortAccount();
                break;
            }case 8: {
                bank.statAccount();
                break;
            }
        }
    } while (choice != 0);
}

void Menu::transactionMenu()
{
    int choice;
    do {
        cout << "\n----- QUAN LY GIAO DICH -----\n";
        cout << "1. Xem lich su giao dich\n";
        cout << "2. Loc theo tai khoan\n";
        cout << "3. Loc theo loai giao dich\n";
        cout << "4. Loc theo thoi gian\n";
        cout << "5. Thong ke\n";
        cout << "6. Sap xep giao dich\n";
        cout << "0. Quay lai\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                firstRow();
                bank.printAllTransactions();
                break;
            } case 2: {
                filterByAccount(bank);
                break;
            } case 3: {
                filterByType(bank);
                break;
            } case 4: {
                filterByDate(bank);
                break;
            } case 5: {
                bank.statTransaction();
                break;
            } case 6: {
                bank.sortTransaction();
                break;
            }
        }
    } while (choice != 0);
}