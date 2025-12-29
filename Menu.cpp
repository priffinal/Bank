#include "Menu.h"
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
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            customerMenu();
            break;
        case 2:
            accountMenu();
            break;
        case 3:
            transactionMenu();
            break;
        }
    } while (choice != 0);   
}

void Menu::customerMenu()
{
    int choice;
    string ID;
    bool ok = false;
    do {
        cout << "\n----- QUAN LY KHACH HANG ----\n";
        cout << "1. Them khach hang\n";
        cout << "2. Sua thong tin\n";
        cout << "3. Hien thong tin\n";
        cout << "4. Xoa khach hang\n";
        cout << "0. Quay lai\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();
        cout << "\n";

        switch (choice) {
        case 1:	{
            string fullName, phone, email, address;
            cout << "Nhap ho ten: "; getline(cin, fullName);
            cout << "Nhap so dien thoai: "; getline(cin, phone);
            cout << "Nhap email: "; getline(cin, email);
            cout << "Nhap dia chi: "; getline(cin, address);

            string newID = bank.addCustomer(fullName, phone, email, address);
            cout << "Tao khach hang thanh cong.\n";
            cout << "ID cua khach hang la: " << newID << endl;
            break;
        }
        case 2: {
            do {
                cout << "Nhap ID khach hang: "; cin >> ID;
                cin.ignore();
                if (bank.searchCustomer(ID) == nullptr) {
                    cout << "Khach hang khong ton tai. Vui long nhap lai.\n";
                    ok = false;
                } 
                else ok = true;
            } while (!ok);
            string name, phone, email, address;
            cout << "Sua thong tin (khong sua thi an Enter)\n";
            cout << "Sua ten: "; getline(cin, name);
            cout << "Sua SDT: "; getline(cin, phone);
            cout << "Sua email: "; getline(cin ,email);
            cout << "Sua dia chi: "; getline(cin, address);
            bank.updateCusInfo(ID, name, phone, email, address); 
            break;
        }
        case 3: {
            do {
                cout << "Nhap ID khach hang: "; cin >> ID;
                cin.ignore();
                if (bank.searchCustomer(ID) == nullptr) {
                    cout << "Khach hang khong ton tai. Vui long nhap lai.\n";
                    ok = false;
                }
                else ok = true;
            } while (!ok);
            bank.showCusInfo(ID);
            break;
        }
        case 4: {
            do {
                cout << "Nhap ID khach hang: "; cin >> ID;
                cin.ignore();
                if (bank.searchCustomer(ID) == nullptr) {
                    cout << "Khach hang khong ton tai. Vui long nhap lai.\n";
                    ok = false;
                }
                else ok = true;
            } while (!ok);
            bank.deleteCustomer(ID);
            cout << "Xoa khach hang thanh cong.\n";
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
    string cusID, accID;
    bool ok = false;
    do {
        bool ok = false;
        cout << "\n----- QUAN LY TAI KHOAN ----\n";
        cout << "1. Mo tai khoan\n";
        cout << "2. Dong tai khoan\n";
        cout << "3. Hien thong tin\n";
        cout << "4. Gui tien\n";
        cout << "5. Rut tien\n";
        cout << "6. Chuyen tien\n";
        cout << "0. Quay lai\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();
        cout << "\n";

        switch (choice) {
            case 1: {
                do {
                    cout << "Nhap ID khach hang: "; cin >> cusID;
                    cin.ignore();
                    if (bank.searchCustomer(cusID) == nullptr) {
                        cout << "Khach hang khong ton tai. Vui long nhap lai.\n";
                        ok = false;
                    } else ok = true;
                } while (!ok);
                int n;
                string newID;
                long long balance;
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
                break;
            } case 2: {
                do {
                    cout << "Nhap ID tai khoan: "; cin >> accID;
                    cin.ignore();
                    if (bank.searchAccount(accID) == nullptr) {
                        cout << "Tai khoan khong ton tai. Vui long nhap lai.\n";
                        ok = false;
                    }
                    else ok = true;
                } while (!ok);
                bank.closeAccount(accID);
                cout << "Dong tai khoan thanh cong.\n";
                break;
            } case 3: {
                do {
                    cout << "Nhap ID tai khoan: "; cin >> accID;
                    cin.ignore();
                    if (bank.searchAccount(accID) == nullptr) {
                        cout << "Tai khoan khong ton tai. Vui long nhap lai.\n";
                        ok = false;
                    }
                    else ok = true;
                } while (!ok);
                bank.showAccInfo(accID);
                break;
            } case 4: {
                do {
                    cout << "Nhap ID tai khoan: "; cin >> accID;
                    cin.ignore();
                    if (bank.searchAccount(accID) == nullptr) {
                        cout << "Tai khoan khong ton tai. Vui long nhap lai.\n";
                        ok = false;
                    }
                    else ok = true;
                } while (!ok);
                Account *acc = bank.searchAccount(accID);
                long long balance;
                cout << "Nhap so tien gui vao: "; cin >> balance;
                bank.deposit(*acc, balance);
                cout << "Chuyen thanh cong " << balance << "VND vao tai khoan.\n";
                break;
            } case 5: {
               do {
                    cout << "Nhap ID tai khoan: "; cin >> accID;
                    cin.ignore();
                    if (bank.searchAccount(accID) == nullptr) {
                        cout << "Tai khoan khong ton tai. Vui long nhap lai.\n";
                        ok = false;
                    }
                    else ok = true;
                } while (!ok);
                Account *acc = bank.searchAccount(accID);
                long long balance;
                cout << "Nhap so tien rut: "; cin >> balance;
                bool result = bank.withdraw(*acc, balance);
                if (result) cout << "Rut thanh cong " << balance << "VND.\n";
                else cout << "Rut that bai.\n";
                break;
            } case 6: {
                string toID;
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
                break;
            }
        }
    } while (choice != 0);
}

void Menu::transactionMenu()
{
    int choice;
    bool ok = false;
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
                 cout << left
                     << setw(12) << "Ma GD"
                     << setw(15) << "TK Nguon"
                     << setw(15) << "TK Nhan"
                     << setw(27) << "Thoi gian"
                     << setw(15) << "So tien"
                     << setw(20) << "Loai"
                     << setw(10) << "Trang thai"
                     << endl;
                 cout << string(114, '-') << endl;
                 bank.printAllTransactions();
                break;
            }   
        }
    } while (choice != 0);
}