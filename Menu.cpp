#include "menu.h"
#include<iostream>
using namespace std;
void menu::drawFrame() {
    for (int i = 0; i < 30; i++) cout << "=";
    cout << "\n";
}

void menu::clearScreen() {
    system("cls");
}

void menu::showMainMenu() {
    clearScreen();
    drawFrame();
    cout << "      NGAN HANG SO TDPBANK\n";
    drawFrame();

    cout << "[1] QUAN LY TAI KHOAN\n";
    cout << "[2] GIAO DICH NGAN HANG\n";
    cout << "[3] QUAN LY KHACH HANG\n";
    cout << "[4] Xem danh sach\n";
    cout << "[0] Thoat\n";
    drawFrame();
    cout << "Nhap lua chon: ";
}
void menu::ShowAccountMenu() {
    clearScreen();
    drawFrame();
    cout << "      QUAN LY TAI KHOAN\n";
    drawFrame();
    cout << "[1] Tao tai khoan\n";
    cout << "[2] Dong tai khoan\n";
    cout << "[3] Xem danh sach tai khoan\n";
    cout << "[0] Quay lai\n";
    drawFrame();
    cout << "Nhap lua chon: ";
}

void menu::ShowTransactionMenu() {
    clearScreen();
    drawFrame();
    cout << "      GIAO DICH NGAN HANG\n";
    drawFrame();
    cout << "[1] Rut tien\n";
    cout << "[2] Nap tien\n";
    cout << "[3] Chuyen khoan\n";
    cout << "[0] Quay lai\n";
    drawFrame();
    cout << "Nhap lua chon: ";
}

void menu::ShowCustomerMenu() {
    clearScreen();
    drawFrame();
    cout << "      QUAN LY KHACH HANG\n";
    drawFrame();
    cout << "[1] Them khach hang\n";
    cout << "[2] Sua thong tin\n";
    cout << "[3] Xoa khach hang\n";
    cout << "[4] Tim kiem khach hang\n";
    cout << "[0] Quay lai\n";
    drawFrame();
    cout << "Nhap lua chon: ";
}
